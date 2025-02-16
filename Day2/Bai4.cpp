// Cho n nhập từ bàn phím (n đủ lớn), phân tích n thành TSNT, tìm ước số nguyên tố (m) lớn nhất của nó, tìm số nguyên tố gần m nhất, tìm số hoàn hảo gần m nhất

#include <bits/stdc++.h>
using namespace std;

void factorize(long long n) {
    for (long long i = 2; i <= sqrt(n); i++) {
        int d = 0;
        while (n % i == 0) {
            n /= i;
            d++;
        }
        if (d > 0) {
            cout << i << "^" << d;
            if (n > 1) {
                cout << " x ";
            }
        }
    }
    if (n > 1) {
        cout << n;
    }
}

long long largestPrimeFactor(long long n) {
    long long max = -1;
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            max = i;
            n /= i;
        }
    }
    if (n > 1) max = n;
    return max;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

long long nearestPrime(long long m) {
    long long lower = m - 1, upper = m + 1;
    while (true) {
        if (isPrime(lower)) return lower;
        if (isPrime(upper)) return upper;
        --lower;
        ++upper;
    }
}

long long nearestPerfectNumber(long long m) {
    long long perfectNumbers[] = {6, 28, 496, 8128, 33550336};
    long long closest = perfectNumbers[0];
    for (long long num : perfectNumbers) {
        if (abs(num - m) < abs(closest - m)) {
            closest = num;
        }
    }
    return closest;
}

int main() {
    long long n;
    cout << "Nhap n: ";
    cin >> n;

    cout << "Phan tich thua so nguyen to: ";
    factorize(n);

    cout << endl;
    long long m = largestPrimeFactor(n);
    cout << "Uoc so nguyen to lon nhat: " << m << endl;

    cout << "So nguyen to gan voi " << m << " nhat la: " << nearestPrime(m) << endl;
    
    cout << "So hoan hao gan voi " << m << " nhat la: " << nearestPerfectNumber(m) << endl;

    return 0;
}