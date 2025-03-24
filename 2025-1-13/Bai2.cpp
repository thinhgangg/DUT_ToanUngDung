// Given two numbers a and b, the task is to find the GCD of the two numbers.

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;

    if (a > b)
        return gcd(b, a % b);
    return gcd(b, a);
}

int main() {
    int a, b;
    cout << "a = "; 
    cin >> a;
    cout << "b = "; 
    cin >> b;
    cout << "UCLN cua " << a << " va " << b << ": " << gcd(a, b);
    return 0;
}