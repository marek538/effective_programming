#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

class CPoint {
public:
    char value = '.';
    int depth_size = 0;
    bool pointedDown = false;

    CPoint() = default;

    explicit CPoint(char value, bool down) : value(value), pointedDown(down) {};
};


class CTriangle {
public:

    vector<vector<CPoint>> triangleOriginal;
    vector<vector<CPoint>> justForReverse;

    // vector<vector<int>> triangle;
    bool baseDown = false;

    CTriangle(vector<vector<CPoint>> original) : triangleOriginal(original), justForReverse(original) {
        baseDown = (triangleOriginal[triangleOriginal.size() - 1].size() > triangleOriginal[0].size());

    }

    int getValueAt(int row, int col) {
        if (row < 0 || row >= triangleOriginal.size() || col < 0 || col >= triangleOriginal[row].size() || triangleOriginal[row][col].value != '-')
            return 0;

        return triangleOriginal[row][col].depth_size;
    }

    // TODO - correct index - save with spaces
    int returnThreeOver(int row, int col) {
        int result = min(getValueAt(row - 1, col - 1), getValueAt(row - 1, col + 1));
        result = min(result, getValueAt(row - 1, col));
        return result + 1;
    }

    int returnNeighbors(int row, int col) {
        return min(getValueAt(row, col - 1), getValueAt(row, col + 1));
    }

//     bool isPointedDown(int row, int col) {
//         // return true;
//         /*if (!baseDown && (col % 2 == 0))
//             return true;
//         if (baseDown && (col % 2 == 1))
//             return true;
//
//         return false;*/
//
//
//     }

    bool isPointedDown(int row, int col) {
        if (!baseDown)
            return triangleOriginal[row][col].pointedDown;
        else
            return !triangleOriginal[row][col].pointedDown;
    }

    int getTrianglesAmount(int layers) {
        return layers*layers;
    }

    int getMaxNumber() {
        int result = 0;
        for (int i = 0; i < triangleOriginal.size(); i++) {
            for (int j = 0; j < triangleOriginal[i].size(); j++) {
                if (triangleOriginal[i][j].value == '-' && isPointedDown(i, j)) {

                    triangleOriginal[i][j].depth_size = returnThreeOver(i,j);
                    result = max(result, triangleOriginal[i][j].depth_size);
                }
            }
            for (int j = 0; j < triangleOriginal[i].size(); j++) {
                if (triangleOriginal[i][j].value == '-' && !isPointedDown(i, j)) {
                    triangleOriginal[i][j].depth_size = returnNeighbors(i, j);
                }

            }
        }
        return getTrianglesAmount(result);
    }

    void testPrintTriangle() {
        for (int i = 0; i < triangleOriginal.size(); i++) {
            for (int j = 0; j < triangleOriginal[i].size(); j++) {
                if (triangleOriginal[i][j].value == ' ')
                    cout  << "  ";
                else
                    cout <<  triangleOriginal[i][j].depth_size << " ";
            }
            cout << endl;
        }
    }

    void reverse() {
        baseDown = !baseDown;
        vector<vector<CPoint>> temp;
        for (int i = justForReverse.size() - 1; i >= 0; i--) {
            temp.push_back(justForReverse[i]);
        }
        justForReverse = temp;
        triangleOriginal = justForReverse;
    }
};

vector<CTriangle> readInput() {
    vector<CTriangle> triangles;

    while (true) {
        int count;
        if (!(cin >> count))
            break;

        if (count == 0)
            break;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<CPoint>> original;
        bool startsDown = false;
        for (int i = 0; i < count; i++) {
            string line;
            original.emplace_back();
            if (!getline(cin, line))
                break;
            for (int j = 0; j < line.size(); j++) {
                bool down = false;
                if (!startsDown)
                    down = (j % 2 == 0);
                else
                    down = (j % 2 == 1);

                original[original.size() - 1].emplace_back(line[j], down);
            }
            startsDown = !startsDown;
        }

        CTriangle t(original);
        triangles.push_back(t);

    }

    return triangles;
}

int processTriangle(CTriangle& triangle) {
    int max1 = triangle.getMaxNumber();
    // triangle.testPrintTriangle();

    // cout << triangle.baseDown << endl;
    // for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
    //     for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
    //         cout << triangle.isPointedDown(i,j) << " ";
    //     }
    //     cout << endl;
    // }

    triangle.reverse();
    int max2 = triangle.getMaxNumber();
    //
    // cout << triangle.baseDown << endl;
    // for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
    //     for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
    //         cout << triangle.isPointedDown(i,j) << " ";
    //     }
    //     cout << endl;
    // }

    return max(max1, max2);
}

void solver(vector<CTriangle>& triangles) {
    for (int i = 0; i < triangles.size(); i++) {
        int tmp = processTriangle(triangles[i]);
        cout << "Triangle #" << i+1 <<"\nThe largest triangle area is " << tmp << ".\n" << endl;
    }
}


// 4
// -------
// -----
// ---
// -
// 0


int main() {
    auto triangles = readInput();
    // unitTests(triangles[0]);
    solver(triangles);
    return 0;

}
/*
void unitTests(CTriangle& triangle) {
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.isPointedDown(i,j) << " ";
        }
        cout << endl;
    }

    triangle.reverse();
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.isPointedDown(i,j) << " ";
        }
        cout << endl;
    }

    triangle.createEmptyIntegerTriangle();
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.getValueAt(i,j) << " ";
        }
    }

    triangle.reverse();
    triangle.triangle[0][0] = 2;
    cout << triangle.getValueAt(0,0) << endl;
    triangle.triangle[0][2] = 2;
    cout << triangle.returnNeighbors(0,1) << endl;
    triangle.triangle[0][1] = 3;
    cout << triangle.returnThreeOver(1,0) << endl;
    cout << triangle.returnThreeOver(0,6) << endl;


    triangle.reverse();
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.triangle[i][j] << " ";
        }
    }
    triangle.reverse();
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.triangle[i][j] << " ";
        }
    }
    for (int i = 0; i < triangle.triangleOriginal.size(); i++) {
        for (int j = 0; j < triangle.triangleOriginal[i].size(); j++) {
            cout << triangle.triangleOriginal[i][j] << " ";
        }
    }
}*/