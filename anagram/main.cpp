#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include <unordered_set>
#include "algorithm"
#include "map"

using namespace std;

class CRecursion2 {
public:
    int k;
//    int count = 0;
    string text;
    set<string> words;
//    string output_word;
//    set<pair<string, vector<bool>>> memoization;

    CRecursion2(int k, string text): k(k), text(text) {}

    void solve() {
//        std::sort(text.begin(), text.end());
//        output_word.resize(k);
        vector<bool> used(text.size(), false);
        recursion(0, "", used);

//        cout << count << endl;

        for (const auto& word : words)
            cout << word << endl;
        cout << words.size() << endl;
    }

    void recursion(int size, string current, vector<bool> &used) {
//        auto tmp = make_pair(current, used);
//        if ( memoization.find(tmp) != memoization.end())
//            return;
//        memoization.insert(tmp);

        if (size == k) {
            words.insert(current);
//            count++;
//            cout << output_word << endl;
        }
        else {
            for (size_t i = 0; i < text.size(); ++i) {
                if (!used[i]) {
                    used[i] = true;
                    recursion(size + 1, current + text[i], used);
                    used[i] = false;
                }
            }
        }
    }
};

class CRecursion
{
public:
    int k;
    string text;

    map<char, int> char_count;
    set<string> results;

    CRecursion(int k, string text): k(k), text(text) {}

    void solve() {
        for (const char& c : text)
            char_count[c]++;

        string current;
        recursion(0, current);

        for (const auto& word : results)
            cout << word << endl;

        cout << results.size() << endl;
    }

    void recursion(int size, string& current) {
        if (size == k) {
            results.insert(current);
        }
        else {
            for (auto& [c, count] : char_count) {
                if (count > 0) {
                    current.push_back(c);
                    count--;
                    recursion(size + 1, current);
                    count++;
                    current.pop_back();
                }
            }
        }
    }
};

int main() {
    while (true) {
        int k = 0;
        cin >> k;

        if (k == 0)
            break;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string text;
        getline(cin, text);

        CRecursion recursion(k, text);
        recursion.solve();
    }

    return 0;
}
