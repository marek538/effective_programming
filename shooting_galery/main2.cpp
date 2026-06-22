
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;
int main() {

    int N;
    while (cin >> N) {
        vector<int> ducks(N);
        for (int i = 0; i < N; i++) cin >> ducks[i];

        if (N < 2) {
            cout << 0 << endl;
            continue;
        }

        // best[i][j] = max počet dobrých kol na intervalu [i,j)
        vector<vector<int>> best(N+1, vector<int>(N+1, 0));

        // délka intervalu
        for (int len = 2; len <= N; len++) {
            for (int i = 0; i + len <= N; i++) {
                int j = i + len;
                if (ducks[i] == ducks[j-1])
                    best[i][j] = 1 + best[i+1][j-1];
                else
                    best[i][j] = max(best[i+1][j], best[i][j-1]);
            }
        }

        cout << best[0][N] << endl;
    }

    return 0;
}
