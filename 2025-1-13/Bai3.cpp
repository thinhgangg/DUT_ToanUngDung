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

int phi(int n) {
    int result = 1;
    for (int i = 2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;

    for (int i = 1; i <= n; i++) 
        cout << "phi("<< i <<") = " << phi(i) << endl; 

    return 0;     
}