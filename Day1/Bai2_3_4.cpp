// viết chương trình nhập n, in ra các ước số của n, đếm các ước số, tính tổng các ước số, tính tích các ước số

#include <iostream>
using namespace std;

void printDivisor(int n) {
    int d = 0;
    cout << "Cac uoc so cua n la: ";
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cout << i << " ";
            d++;
        }
    }
    cout << "\nSo cac uoc so cua " << n << " la: ";
    cout << d << endl;
}

void sumDivisor(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            s += i;
        }
    }
    cout << "Tong cac uoc so cua " << n << " la: ";
    cout << s << endl;
}

void productDivisor(int n) {
    int p = 1;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            p *= i;
        }
    }
    cout << "Tich cac uoc so cua " << n << " la: ";
    cout << p << endl;
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;
    printDivisor(n);
    sumDivisor(n);
    productDivisor(n);
    return 0;
}