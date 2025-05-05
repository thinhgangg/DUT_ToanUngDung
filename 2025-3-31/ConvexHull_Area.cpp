#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
struct Point {
    double x, y;
};

double polygonArea(const vector<Point>& points) {
    int n = points.size();
    double area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; //Diem ke tiep ,vong lap diem dau neu can
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return abs(area) / 2.0;
}

int main() {
    vector<Point> polygon;
	polygon.push_back({0, 0});
	polygon.push_back({4, 0});
	polygon.push_back({4, 3});
	polygon.push_back({0, 3});
    cout << polygonArea(polygon) << endl;
    return 0;
}
