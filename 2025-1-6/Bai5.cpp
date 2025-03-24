// viết chương trình nhập n, kiểm tra n có phải là số hoàn hảo hay không

#include <iostream>
using namespace std;

bool perfectNumber(int n) {
    int sum = 0;
    for (int i = 1; i <= n/2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;

    if (perfectNumber(n)) {
        cout << n << " la so hoan hao";
    } else cout << n << " khong la so hoan hao";
    return 0;
}
