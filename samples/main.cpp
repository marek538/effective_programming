#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;


class CSample {
public:
    int time;
    int value;
};

struct CompareMin {
    bool operator()(const CSample& a, const CSample& b) const {
        return a.value > b.value;
    }
};

struct CompareMax {
    bool operator()(const CSample& a, const CSample& b) const {
        return a.value < b.value;
    }
};


class CAggregate {
public:
    int results = 0;

    virtual void removeValue(CSample sampleToRemove) = 0;

    virtual void addValue(CSample sampleToAdd) = 0;

    virtual double returnSignificant() = 0;

    virtual bool isEmpty() = 0;

    virtual ~CAggregate() = default;

};

class CAggregateMin : public CAggregate {
public:
//    TODO - use correct heap or read what the vector does
    priority_queue<CSample, vector<CSample>, CompareMin> minHeap;

    void addValue(CSample value) override
    {
        minHeap.push(value);
    }

    bool isEmpty() override
    {
        return minHeap.empty();
    }

    double returnSignificant() override
    {
        return minHeap.top().value;
    }

    void removeValue(CSample sampleToRemove) override
    {
        while(!minHeap.empty() && (minHeap.top().time <= sampleToRemove.time))
            minHeap.pop();
    }
};

class CAggregateMax : public CAggregate {
public:
    priority_queue<CSample, vector<CSample>, CompareMax> maxHeap;

    void addValue(CSample value) override {
        maxHeap.push(value);
    }

    bool isEmpty() override
    {
        return maxHeap.empty();
    }

    double returnSignificant() override {
        return maxHeap.top().value;
    }

    void removeValue(CSample sampleToRemove) override
    {
        while(!maxHeap.empty() && (maxHeap.top().time <= sampleToRemove.time ))
            maxHeap.pop();
    }

};

class CAggregateAvg : public CAggregate {
public:
    double sum = 0;
    int count = 0;

    void removeValue(CSample value) override {
        sum -= value.value;
        count--;
    }

    void addValue(CSample value) override {
        sum += value.value;
        count++;
    }

    bool isEmpty() override{
        return (count == 0);
    }

    double returnSignificant() override {
        return double((double(sum) / double(count)));
    }
};


class CRule {
public:
    bool bigger;
    CAggregate *agg;
    int length;

    CRule(string s) {
        string rel, func;
        stringstream ss(s);
        ss >> rel >> func >> length;

        bigger = (rel == "gt");

        if (func == "avg")
            agg = new CAggregateAvg;
        else if (func == "min")
            agg = new CAggregateMin;
        else
            agg = new CAggregateMax;
    }

    ~CRule() {
        delete agg;
    }
};

class CProblem {
public:
    vector<CSample> samples;
    vector<CRule*> rules;

    ~CProblem() {
        for (auto rule : rules)
            delete rule;
    }

    int slidingWindow(CRule* rule) {
        int firstIndex = 0;
        for(int i = 0; i < (int)samples.size(); i++)
        {
            while(samples[i].time - samples[firstIndex].time > rule->length)
            {
                rule->agg->removeValue(samples[firstIndex]);
                firstIndex++;
            }

            if(!rule->agg->isEmpty())
            {
                double res = rule->agg->returnSignificant();
                if(rule->bigger && (res < samples[i].value))
                    rule->agg->results++;
                else if(!rule->bigger && (res > samples[i].value))
                    rule->agg->results++;
            }

            rule->agg->addValue(samples[i]);
        }

        return rule->agg->results;
    }

    void printResults() {
        for (int i = 0; i < (int)rules.size(); i++) {
            cout << slidingWindow(rules[i]) << endl;
        }
    }

};

CProblem* readInput() {
    CProblem *problem = new CProblem();

    int samplesCount;
    if(!(cin >> samplesCount))
        return nullptr;

    problem->samples.reserve(samplesCount);

    for (int i = 0; i < samplesCount; ++i) {
        int T, V;


        if(!(cin >> T >> V))
            return nullptr;

        CSample sample;
        sample.time = T;
        sample.value = V;
        problem->samples.push_back(sample);

    }

    int rulesCount = 0;

    if(!(cin >> rulesCount))
        return nullptr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    for (int i = 0; i < rulesCount; ++i) {
        string line;
        getline(cin, line);

        CRule* rule = new CRule(line);
        problem->rules.push_back(rule);

    }
    return problem;
}

int main() {
    // list<int> values = {1,2,3};
    // auto it =  find(values.begin(), values.end(), 1);

    try {
        while (true) {
            auto problem = readInput();

            if(problem == nullptr)
                break;

            if (!cin) {
                delete problem;
                break;
            }

            problem->printResults();
            delete problem;
        }
    }
    catch (...) {
    }
    return 0;
}