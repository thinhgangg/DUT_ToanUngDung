#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

// Point
struct Point {
    double x, y;
    int id;
    //Overload operator
    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
     bool operator==(const Point& other) const {
         return x == other.x && y == other.y;
     }
};

// Tich co huong
double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Binh phuong khoang cach giua hai diem
double distSq(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// Dien tich bao loi (Shoelace)
double polygonArea(const vector<Point>& polygon) {
    double area = 0.0;
    int n = polygon.size();
    if (n < 3) return 0.0;

    for (int i = 0; i < n; ++i) {
        area += (polygon[i].x * polygon[(i + 1) % n].y);
        area -= (polygon[i].y * polygon[(i + 1) % n].x);
    }
    return fabs(area) / 2.0;
}

bool isInside(const vector<Point>& hull, Point p, double epsilon = 1e-9) {
    int n = hull.size();
    if (n < 3) return false;

    for (int i = 0; i < n; ++i) {
        if (cross_product(hull[i], hull[(i + 1) % n], p) < -epsilon) {
            return false;
        }
    }
    return true;
}
// Thuật toán Monotone Chain (Andrew's Algorithm)
vector<Point> monotoneChain(vector<Point>& points) {
    int n = points.size();
    if (n <= 2) {
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        return points;
    }
    sort(points.begin(), points.end());
    vector<Point> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull.back(), points[i]) <= 1e-9) {
             hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    int lower_hull_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
         while (hull.size() > lower_hull_size && cross_product(hull[hull.size() - 2], hull.back(), points[i]) <= 1e-9) {
             hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}

// === THUẬT TOÁN JARVIS MARCH (Gift Wrapping) ===
vector<Point> jarvisMarch(const vector<Point>& points) {
    int n = points.size();
    vector<Point> hull;

    if (n < 3) {
         vector<Point> temp = points;
         if (n == 2 && temp[0] == temp[1]) {
            temp.pop_back();
         }
         return temp;
    }

    int start_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].y < points[start_idx].y ||
           (points[i].y == points[start_idx].y && points[i].x < points[start_idx].x)) {
            start_idx = i;
        }
    }

    int current_idx = start_idx;
    int next_idx;
    double epsilon = 1e-9; 

    do {
        hull.push_back(points[current_idx]);
        next_idx = (current_idx + 1) % n;

        for (int i = 0; i < n; ++i) {
            double orientation = cross_product(points[current_idx], points[next_idx], points[i]);
            if (orientation > epsilon) {
                next_idx = i;
            } else if (fabs(orientation) < epsilon) {
                if (distSq(points[current_idx], points[i]) > distSq(points[current_idx], points[next_idx])) {
                    next_idx = i;
                }
            }
        }
        current_idx = next_idx;
    } while (current_idx != start_idx); 

    return hull;
}

vector<Point> Scanning(const std::vector<Point>& points_const) {
    int n = points_const.size();
    std::vector<Point> hull;
    if (n < 3) {
        std::vector<Point> temp = points_const;
        if (n == 2 && temp[0] == temp[1]) {
            temp.pop_back();
        }
        return temp;
    }
    std::vector<Point> points = points_const;
    int p0_idx = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].y < points[p0_idx].y ||
           (points[i].y == points[p0_idx].y && points[i].x < points[p0_idx].x)) {
            p0_idx = i;
        }
    }
    std::swap(points[0], points[p0_idx]);
    Point p0 = points[0];
    double epsilon = 1e-9; 
    auto comparePoints = [&](const Point& a, const Point& b) {
        double order = cross_product(p0, a, b);

        if (std::fabs(order) < epsilon) { 
            return distSq(p0, a) < distSq(p0, b);
        }
        return order > 0;
    };

    std::sort(points.begin() + 1, points.end(), comparePoints);
    hull.push_back(points[0]);
     if (n >= 2 && !(points[1] == points[0])) {
        hull.push_back(points[1]);
     }
    for (int i = 2; i < n; ++i) {
        while (hull.size() >= 2) {
            Point top = hull.back();
            Point next_to_top = hull[hull.size() - 2];
            if (cross_product(next_to_top, top, points[i]) <= epsilon) {
                hull.pop_back();
            } else {
                break;
            }
        }
        if (hull.empty() || !(points[i] == hull.back())) {
             hull.push_back(points[i]);
        }

    }
    return hull; 
}

int findTangent_Linear(const Point& p, const std::vector<Point>& mini_hull) {
    int m = mini_hull.size();
    if (m == 0) return -1; 
    if (m == 1) return 0; 

    int best_idx = 0;
    double max_cross_prod = -std::numeric_limits<double>::infinity(); 
     max_cross_prod = cross_product(p, mini_hull[0], mini_hull[0]); 
     for (int i = 1; i < m; ++i) {
         double current_cp = cross_product(p, mini_hull[best_idx], mini_hull[i]);
         if (current_cp > 1e-9) {
             best_idx = i;
         } else if (std::fabs(current_cp) < 1e-9) {
              if (distSq(p, mini_hull[i]) > distSq(p, mini_hull[best_idx])) {
                  best_idx = i;
              }
         }
     }
    return best_idx;
}

std::vector<Point> Shattering(const std::vector<Point>& points_const) {
    int n = points_const.size();
    std::vector<Point> final_hull;
    if (n < 3) {
        std::vector<Point> temp = points_const;
        if (n == 2 && temp[0] == temp[1]) temp.pop_back();
        return temp;
    }

    std::vector<Point> points = points_const;
    double epsilon = 1e-9;
    for (int t = 1; ; ++t) {
        long long m_ll = 1LL << (1LL << t);
        if (m_ll > n) m_ll = n;
        int m = static_cast<int>(m_ll);
        int num_groups = (n + m - 1) / m;
        std::vector<std::vector<Point>> mini_hulls(num_groups);
        for (int i = 0; i < num_groups; ++i) {
            std::vector<Point> group;
            int start = i * m;
            int end = std::min((i + 1) * m, n);
            for (int j = start; j < end; ++j) {
                group.push_back(points[j]);
            }
            mini_hulls[i] = Scanning(group);
        }
        final_hull.clear();
        int start_idx_global = 0;
        for (int i = 1; i < n; ++i) {
             if (points[i].y < points[start_idx_global].y ||
               (points[i].y == points[start_idx_global].y && points[i].x < points[start_idx_global].x)) {
                start_idx_global = i;
            }
        }
        Point current_p = points[start_idx_global];
        for (int h_count = 0; h_count < m; ++h_count) {
            final_hull.push_back(current_p);
            Point best_q = current_p;
            for (int i = 0; i < num_groups; ++i) {
                if (mini_hulls[i].empty()) continue;
                int tangent_idx = findTangent_Linear(current_p, mini_hulls[i]);
                if (tangent_idx != -1) {
                    Point q_i = mini_hulls[i][tangent_idx];
                    if (best_q == current_p || cross_product(current_p, best_q, q_i) > epsilon) {
                        best_q = q_i;
                    } else if (std::fabs(cross_product(current_p, best_q, q_i)) < epsilon) {
                         if (distSq(current_p, q_i) > distSq(current_p, best_q)) {
                             best_q = q_i;
                         }
                    }
                }
            }
            current_p = best_q;
            if (current_p == final_hull[0]) {
                 return final_hull;
            }
        }
         if (m == n) {
             return final_hull;
         }


    }
    return final_hull;
}

bool isLeftTurn(Point a, Point b, Point c, double epsilon = 1e-9) {
    return cross_product(a, b, c) > epsilon;
}
bool isRightTurn(Point a, Point b, Point c, double epsilon = 1e-9) {
     return cross_product(a, b, c) < -epsilon;
}
bool isCollinear(Point a, Point b, Point c, double epsilon = 1e-9) {
    return std::fabs(cross_product(a, b, c)) < epsilon;
}
vector<Point> mergeHulls(const vector<Point>& hull_L, const vector<Point>& hull_R) {
    int nL = hull_L.size();
    int nR = hull_R.size();
    vector<Point> mergedHull;
    if (nL == 0) return hull_R;
    if (nR == 0) return hull_L;

    int idxL_max_x = 0;
    for (int i = 1; i < nL; ++i) {
        if (hull_L[i].x > hull_L[idxL_max_x].x) {
            idxL_max_x = i;
        }
    }
    int idxR_min_x = 0;
    for (int i = 1; i < nR; ++i) {
        if (hull_R[i].x < hull_R[idxR_min_x].x) {
            idxR_min_x = i;
        }
    }

    int p_up_idx = idxL_max_x;
    int q_up_idx = idxR_min_x;
    bool changed = true;
    while (changed) {
        changed = false;
        int next_p_idx = (p_up_idx + 1) % nL;
        if (isLeftTurn(hull_R[q_up_idx], hull_L[p_up_idx], hull_L[next_p_idx])) {
            p_up_idx = next_p_idx;
            changed = true;
        }
        int prev_q_idx = (q_up_idx - 1 + nR) % nR;
         if (isLeftTurn(hull_L[p_up_idx], hull_R[q_up_idx], hull_R[prev_q_idx])) {
             q_up_idx = prev_q_idx;
             changed = true;
         }
    }

    int p_low_idx = idxL_max_x;
    int q_low_idx = idxR_min_x;
    changed = true;
    while (changed) {
        changed = false;
        int prev_p_idx = (p_low_idx - 1 + nL) % nL;
         if (isRightTurn(hull_R[q_low_idx], hull_L[p_low_idx], hull_L[prev_p_idx])) {
            p_low_idx = prev_p_idx;
            changed = true;
        }
        int next_q_idx = (q_low_idx + 1) % nR;
         if (isRightTurn(hull_L[p_low_idx], hull_R[q_low_idx], hull_R[next_q_idx])) {
             q_low_idx = next_q_idx;
             changed = true;
         }
    }
    int current_idx = p_low_idx;
    while (true) {
        mergedHull.push_back(hull_L[current_idx]);
        if (current_idx == p_up_idx) break;
        current_idx = (current_idx + 1) % nL;
    }
    current_idx = q_up_idx;
     while (true) {
        mergedHull.push_back(hull_R[current_idx]);
        if (current_idx == q_low_idx) break;
        current_idx = (current_idx + 1) % nR;
    }

    return mergedHull;
}

vector<Point> dacHullRecursive(const vector<Point>& sorted_points) {
    int n = sorted_points.size();
    const int BASE_CASE_SIZE = 5;
    if (n <= BASE_CASE_SIZE) {
        vector<Point> base_case_points = sorted_points;
        return Scanning(base_case_points);
    }
    int mid = n / 2;
    vector<Point> left_points(sorted_points.begin(), sorted_points.begin() + mid);
    vector<Point> right_points(sorted_points.begin() + mid, sorted_points.end());

    vector<Point> hull_L = dacHullRecursive(left_points);
    vector<Point> hull_R = dacHullRecursive(right_points);
    return mergeHulls(hull_L, hull_R);
}

// DevideAndConquer
vector<Point> DevideAndConquer(const vector<Point>& points_const) {
    int n = points_const.size();
    if (n == 0) {
        return {};
    }
    vector<Point> points = points_const;
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y;
    });
     points.erase(unique(points.begin(), points.end()), points.end());
     n = points.size();

     if (n < 3) {
         return points;
     }
    return dacHullRecursive(points);
}
// MAIN
int main() {
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
    }

    // --- 1. Xác định bao lồi ---
    vector<Point> original_points = points;
    vector<Point> convexHullPoints = monotoneChain(points);
    // vector<Point> convexHullPoints = jarvisMarch(points);
    // vector<Point> convexHullPoints = Scanning(points);
    // vector<Point> convexHullPoints = Shattering(points);
    // vector<Point> convexHullPoints = DevideAndConquer(points);


    if (convexHullPoints.empty()) {
        cout << "Khong the xac dinh bao loi (can it nhat 1 diem).\n";
        return 1;
    }

    cout << "Cac diem nam tren bao loi: ";
    vector<bool> isOnHull(n, false);
    vector<Point> sorted_hull = convexHullPoints;
    sort(sorted_hull.begin(), sorted_hull.end());

    for (const auto& p_hull : convexHullPoints) {
        cout << " (" << p_hull.x << ", " << p_hull.y << ") ";
        for(int i = 0; i < n; ++i) {
            if (original_points[i].id == p_hull.id) {
                 isOnHull[i] = true;
                 break;
             }
        }
    }
    cout << endl;

    int k = convexHullPoints.size();
    double area = polygonArea(convexHullPoints);
    cout << fixed << setprecision(6);
    cout << "Dien tich bao loi: " << area << endl;
    double minEdgeSq = numeric_limits<double>::max();
    if (k >= 2) {
        for (int i = 0; i < k; ++i) {
            minEdgeSq = min(minEdgeSq, distSq(convexHullPoints[i], convexHullPoints[(i + 1) % k]));
        }
        cout << "Do dai canh be nhat cua bao loi: " << sqrt(minEdgeSq) << endl;
    } else {
         cout << "Khong co canh nao trong bao loi (it hon 2 diem).\n";
    }
    vector<Point> insidePoints;
    cout << "Cac diem nam ben trong bao loi: ";
    bool foundInside = false;
    for (int i = 0; i < n; ++i) {
        if (!isOnHull[i]) {
            if (isInside(convexHullPoints, original_points[i])) {
                insidePoints.push_back(original_points[i]);
                cout << " (" << original_points[i].x << ", " << original_points[i].y << ") ";
                foundInside = true;
            }
        }
    }
    if (!foundInside) {
        cout << "Khong co diem nao nam ben trong.";
    }
    cout << endl;
    double minInsideDistSq = numeric_limits<double>::max();
    int m = insidePoints.size();
    if (m >= 2) {
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                minInsideDistSq = min(minInsideDistSq, distSq(insidePoints[i], insidePoints[j]));
            }
        }
         cout << "Khoang cach ngan nhat giua cac diem ben trong: " << sqrt(minInsideDistSq) << endl;
    } else {
        cout << "Khong du diem ben trong de tinh khoang cach ngan nhat (can it nhat 2 diem).\n";
    }
    return 0;
}