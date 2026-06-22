#include <iostream>
#include <map>

using namespace std;

class CProblem{
public:
    double amount;
    map<double, int> coinsBuyer;
    map<double, int> coinsSeller;

    void solve()
    {
        // od nejvetsiho po nejmensi
//        for (auto it = coins.rbegin(); it != coins.rend(); ++it) {
//            cout << it->first << " → " << it->second << "\n";
//        }
    }
};

int main() {
    while(true)
    {
        CProblem problem;
        double amount;
        cin >> amount;

        problem.amount = amount * 100;
        if(amount < 0)
            break;


        // no boilerplate whatsoever
        double value = 0;
        int coins = 0;
        char x;
        while(true)
        {
            cin >> value;
            if(value < 0)
                break;

            cin >> coins >> x;
            value = value * 100;
            if(value >= 0)
                problem.coinsBuyer[value] = coins;
        }

        while(true)
        {
            cin >> value;
            if(value < 0)
                break;

            cin >> coins >> x;
            value = value * 100;
            if(value >= 0)
                problem.coinsSeller[value] = coins;
        }

        problem.solve();
    }
    return 0;
}
