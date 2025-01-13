// // Given a number n, print all primes smaller than or equal to n. It is also given that n is a small number. 

#include <bits/stdc++.h>
using namespace std;

void SieveOfEratosthenes(int n) {
    vector<bool> prime(n + 1, true);
    for (int i = 2; i * i <= n; i++) {
        if (prime[i] == true) {
            for (int j = i * i; j <= n; j += i) 
                prime[j] = false;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (prime[i]) 
            cout << i << " ";
    }
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Cac so nguyen to nho hon hoac bang " << n << endl;
    SieveOfEratosthenes(n);
    return 0;
}
