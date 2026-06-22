#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void getSteps(int ponork, int roads_count, vector<double>& roads)
{
    int total_steps = 0;
    double remove_from_next = 0;
    double epsilon = 1e-9;

    for(int i = 0; i < roads_count; i++){
        if(remove_from_next > epsilon)
            total_steps++;

        roads[i] = roads[i] - remove_from_next;
        int steps_on_wall = int(roads[i] / ponork);
        roads[i] = roads[i] - steps_on_wall * ponork;

        // Calculate how much to remove from the next road segment
        if(roads[i] > epsilon)
            remove_from_next = sqrt(ponork * ponork - roads[i] * roads[i]);
        else
            remove_from_next = 0;

        total_steps += steps_on_wall;
    }

    if(roads[roads.size() - 1] >= (double)ponork / 2.0 - epsilon){
        total_steps++;
    }

    cout << "Strazny ujde " << total_steps << " ponorku." << endl;
}

void solve() {
    int ponork, roads_count;
    cin >> ponork >> roads_count;

    vector<double> roads(roads_count);
    for (int i = 0; i < roads_count; ++i) {
        cin >> roads[i];
    }

    getSteps(ponork, roads_count, roads);
}

int main() {
    int cases;
    if (cin >> cases) {
        while (true) {
            cases--;

            solve();
            if (cases <= 0) break;
        }
    }
    return 0;
}
