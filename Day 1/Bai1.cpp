// Viết chương trình sử dụng hàm phân tích thừa số nguyên tố của số nguyên n (n > 1) được nhập từ bàn phím

#include <iostream>
#include <math.h>
using namespace std;

void factorize(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
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

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;
    
    cout << "Phan tich thua so nguyen to: ";
    factorize(n);
    return 0;
}
