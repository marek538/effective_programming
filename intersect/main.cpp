#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

long long orientation(const Point& a, const Point& b, const Point& c) {
    long long v = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (v == 0) return 0;
    return (v > 0 ? 1 : 2);
}

bool onSegment(const Point& a, const Point& b, const Point& c) {
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

bool segments(long long x1, long long y1, long long x2, long long y2,
              long long x3, long long y3, long long x4, long long y4) {

    Point p1{x1, y1}, q1{x2, y2};
    Point p2{x3, y3}, q2{x4, y4};

    long long o1 = orientation(p1, q1, p2);
    long long o2 = orientation(p1, q1, q2);
    long long o3 = orientation(p2, q2, p1);
    long long o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;

    return false;
}

bool solve(long long x1, long long y1, long long x2, long long y2,
           long long xL, long long yT, long long xR, long long yB) {

    if (xL > xR) swap(xL, xR);
    if (yT < yB) swap(yT, yB);

    bool p1_inside = (xL <= x1 && x1 <= xR && yB <= y1 && y1 <= yT);
    bool p2_inside = (xL <= x2 && x2 <= xR && yB <= y2 && y2 <= yT);

    if (p1_inside || p2_inside) {
        return true;
    }

    return segments(x1, y1, x2, y2, xL, yT, xR, yT)
           || segments(x1, y1, x2, y2, xL, yB, xR, yB)
           || segments(x1, y1, x2, y2, xL, yT, xL, yB)
           || segments(x1, y1, x2, y2, xR, yT, xR, yB);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    while (n--) {
        long long x1, y1, x2, y2;
        long long xL, yT, xR, yB;

        if (!(cin >> x1 >> y1 >> x2 >> y2 >> xL >> yT >> xR >> yB)) break;

        if (solve(x1, y1, x2, y2, xL, yT, xR, yB)) {
            cout << "T" << endl;
        } else {
            cout << "F" << endl;
        }
    }

    return 0;
}