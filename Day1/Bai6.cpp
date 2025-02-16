// viết chương trình in ra các số hoàn hảo trong khoảng từ 0 đến n

#include <iostream>
using namespace std;

bool perfectNumber(int n) {
    int sum = 0;
    for (int i = 1; i <= n/2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    if (sum == n) {
        return 1;
    }
    return 0;
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;

    cout << "Cac so hoan hao trong khoang tu 0 den " << n << " la: ";
    bool found = false; 
    for (int i = 0; i < n; i++) {
        if (perfectNumber(i)) {
            cout << i << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "khong co";
    }
    return 0;
}
