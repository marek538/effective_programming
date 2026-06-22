#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;


class CProblemOld {
public:
    map<int, vector<uint>> intervals;

    void solve(){

        vector<pair<int, int>> inter;

        for (auto &pair : intervals) {
            if(pair.second.size() < 2) continue;

            for (int i = 0; i < pair.second.size(); i++) {
                for (int j = i + 1; j < pair.second.size(); j++) {
                    inter.emplace_back( (int)pair.second[i], (int)pair.second[j] );
                }
            }
        }

        if (inter.empty()) {
            cout << 0 << endl;
            return;
        }

        sort(inter.begin(), inter.end(),
             [](const pair<int, int> &a, const pair<int, int> &b) {
                 return (a.second - a.first) > (b.second - b.first);
             });


        // nasel jsem nejaky fenwick tree

    }
};


class LonegstPalindromicSubsequence{
public:
    int lpsDP(const vector<int>& ducks) {
        int ducksLength = (int)ducks.size();
        vector<vector<int>> dp(ducksLength, vector<int>(ducksLength, 0));


    }
};

int main() {
    int count;

    while(cin >> count)
    {
        LonegstPalindromicSubsequence problem;
        vector<int> data;
        for(int i = 0; i < count; i++)
        {
            int dc;
            if (!(cin >> dc)) {
                return 0;
            }
            data.push_back(dc);
        }

        cout << problem.lpsDP(data) << endl;
    }
    return 0;
}
