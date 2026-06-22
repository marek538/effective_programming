#include <iostream>
#include <map>
#include <algorithm>
#include "vector"
using namespace std;

class CProblem {
public:
    int Empty;
    int Full;
    int realWeight;
    vector<pair<int, int>> coins;
    // price, weight

    map<int, pair<bool, int>> memo;
    // weight, price


    pair<bool, int> getMinimum(pair<bool, int> left, pair<bool, int> right)
    {
        if(left.first && right.first)
            return {true, min(left.second, right.second)};
        if(!left.first && !right.first)
            return {false, min(left.second, right.second)};
        if(left.first)
            return left;
        return right;
    }

    pair<bool, int> subTree(int weight, int price)
    {
        if(memo.find(weight) != memo.end())
            return memo[weight];

        pair<bool, int> minimum = {false, INT32_MAX};

        for(auto coin : coins)
        {
            if(weight - coin.second < 0)
                minimum = getMinimum(minimum, {false, coin.first});
            else if(weight - coin.second == 0)
                minimum = getMinimum(minimum, {true, coin.first});
            else {
                auto tmp = subTree(weight - coin.second, price + coin.first);
                tmp.second += coin.first;
                minimum = getMinimum(minimum, tmp);
            }
        }

        memo[weight] = minimum;
        return minimum;
    }

    void solve()
    {
        sort(coins.begin(), coins.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        realWeight = Full - Empty;

        auto tmp = subTree(realWeight, 0);

        if(!memo[realWeight].first)
            cout << "This is impossible." << endl;
        else
            cout << "The minimum amount of money in the piggy-bank is " << memo[realWeight].second << "." << endl;

    }
};

int main() {
    int T;
    cin >> T;

    for(int i = 0; i < T; i++)
    {
        CProblem problem;

        cin >> problem.Empty >> problem.Full;

        int N;
        cin >> N;
        for(int j = 0; j < N; j++)
        {
            int price, weight;
            cin >> price >> weight;
            problem.coins.emplace_back(price, weight);
        }

        problem.solve();
    }


    return 0;
}
