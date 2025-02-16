// slide 34 - modular exponentiation

#include <iostream>
using namespace std;

int modpow(int x, int n, int m) {
    if (n == 0) return 1 % m;
    long long u = modpow(x, n/2, m);
    u = (u * u) % m;
    if (n % 2 == 1) u = (u * x) % m;
    return u;
}

int main() {
    int x, n, m;

    cout << "x = ";
    cin >> x;

    cout << "n = ";
    cin >> n;

    cout << "m = ";
    cin >> m;  
    
    cout << modpow(x, n, m);

    return 0;
}