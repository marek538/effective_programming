#include <iostream>
#include <vector>
#include "cmath"
#include "bits/stdc++.h"

using namespace std;

//towers of hanoi
void solve(queue<int> &containers)
{
//
    int result = 0;
    int last = containers.front();
    while(!containers.empty()) {
        int current = containers.front();
        containers.pop();
        if(last != current) {
            // tady odjebu vse nad
            result += (pow(2, (int)containers.size())) - 1;
            // tady pohnu tim realnym frajerem
            result += 1;
            last = 3 - (last + current);
        }
        else
            last = current;
    }

    // no nic - pri poslednim presunu nemusim posouvat hlavu sem a tam
//    if(containers.size() >= 3 && (containers[containers.size() - 1] != containers[containers.size() - 2])) {
//        result = max(result - 1,0);
//    }


    cout << "Je treba "<< result << " presunu." << endl;
}

int main() {
    int length;
    cin >> length;

    for (int i = 0; i < length; ++i) {
        int conts;
        cin >> conts;

        queue<int> containers;
        for (int j = 0; j < conts; ++j) {
            int tmp=0;
            cin >> tmp;
            containers.push(tmp);
        }

        solve(containers);
    }

    return 0;
}
