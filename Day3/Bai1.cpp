// slide 32 - modular arithmetic

#include <iostream>
using namespace std;

int main() {
    int x, y, m;

    cout << "x = ";
    cin >> x;

    cout << "y = ";
    cin >> y;

    cout << "m = ";
    cin >> m;

    // (x + y) mod m = (x mod m + y mod m) mod m
    int l1 = (x + y) % m;
    int r1 = ((x % m + y % m) % m);
    cout << "(x + y) mod m = " << l1 << " (x mod m + y mod m) mod m = " << r1 << endl;
    cout << (l1 == r1 ? "true" : "flase") << endl;

    // (x - y) mod m = (x mod m - y mod m) mod m
    int l2 = (x - y) % m;
    int r2 = ((x % m - y % m) % m);
    cout << "(x - y) mod m = " << l2 << " (x mod m - y mod m) mod m = " << r2 << endl;
    cout << (l2 == r2 ? "true" : "flase") << endl;

    // (x * y) mod m = (x mod m * y mod m) mod m
    int l3 = (x * y) % m;
    int r3 = ((x % m * y % m) % m);
    cout << "(x * y) mod m = " << l3 << " (x mod m * y mod m) mod m = " << r3 << endl;
    cout << (l3 == r3 ? "true" : "flase") << endl;

    // x^n mod m = (x mod m)^n mod m
    int n;
    cout << "n = ";
    cin >> n;
    int l4 = 1, r4 = 1;
    for (int i = 0; i < n; i++) {
        l4 = (l4 * x) % m;
        r4 = (r4 * (x % m)) % m;
    }
    cout << "x^n mod m = " << l4 <<  " (x mod m)^n mod m = " << r4 << endl;
    cout << (l4 == r4 ? "true" : "flase") << endl;

    return 0;
}