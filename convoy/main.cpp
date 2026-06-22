#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <set>
#include <limits>
#include <map>

using namespace std;

class batch
{
    int weight = 0;
    int minSpeed = std::numeric_limits<int>::max();
};

double getTime(int length, int speed)
{
    return static_cast<double>(length) / speed;
}

class problem {
public:

    int maxLoad;
    int length;
    vector<pair<int, int>> cars;

    map<uint, double> memoization;

    void recursion(uint index)
    {
        // case spojim
        double time = std::numeric_limits<double>::max();;
        int weight = 0;
        int minSpeed = std::numeric_limits<int>::max();

        for(uint i = index; i < cars.size(); ++i)
        {
            weight += cars[i].first;
            if(weight > maxLoad)
                break;

            minSpeed = min(minSpeed, cars[i].second);
            double rest = 0.0;
            if(i + 1 < cars.size())
                rest = memoization[i + 1];

            time = min(time, getTime(length, minSpeed) + rest);
        }

        // case nespojim
        auto timeSeparated = getTime(length, cars[index].second) + memoization[index + 1];
        time = min(time, timeSeparated);

        memoization[index] = time;
    }

    double solve()
    {
        if(cars.empty())
            return 0.0;
        if(cars.size() == 1)
            return getTime(length, cars[0].second)*60;


        memoization[cars.size() - 1] = getTime(length, cars.back().second);
        for(int i = (int)cars.size() - 2; i >= 0; --i)
        {
            recursion(i);
        }
        return memoization[0] * 60;
    }

};


int main() {
    while(true)
    {
        int maxLoad, length, n;
        std::cin >> maxLoad >> length >> n;

        if(maxLoad == 0 && length == 0 && n == 0)
            break;


        vector<pair<int, int>> cars;
        for (int i = 0; i < n; ++i) {
            int weight, speed;
            std::cin >> weight >> speed;
            if(weight > maxLoad)
                continue;
            cars.emplace_back(weight, speed);
        }

        problem p;
        p.maxLoad = maxLoad;
        p.length = length;
        p.cars = cars;


        cout << fixed << setprecision(1) << p.solve() << endl;
    }

    return 0;
}
