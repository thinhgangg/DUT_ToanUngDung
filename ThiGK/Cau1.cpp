#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isNguyenTo(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isHoanHao(int n) {
    if (n <= 1) return false;
    int sum = 1;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n/i) sum += n/i;
        }
    }
    return sum == n;
}

int nguyenToLonNhat(int n) {
    int max = 1;
    while (n % 2 == 0) {
        max = 2;
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            max = i;
            n /= i;
        }
    }
    if (n > 2) max = n;
    return max;
}

int main() {
    int N = 95300;
    
    int M = nguyenToLonNhat(N);
    cout << "Uoc nguyen to lon nhat cua " << N << " : M = " << M << endl;
    
    vector<int> perfectNumbers;
    int sumPerfect = 0;
    for (int i = 1; i < M; i++) {
        if (isHoanHao(i)) {
            perfectNumbers.push_back(i);
            sumPerfect += i;
        }
    }
    
    cout << "\nSo luong so hoan hao nho hon " << M << ": " << perfectNumbers.size() << endl;
    cout << "Cac so hoan hao: ";
    for (int num : perfectNumbers) {
        cout << num << " ";
    }
    cout << "\nTong cac so hoan hao: " << sumPerfect << endl;
    
    vector<int> primes;
    int sumPrimes = 0;
    for (int i = 2; i < M; i++) {
        if (isNguyenTo(i)) {
            primes.push_back(i);
            sumPrimes += i;
        }
    }
    
    cout << "\nSo luong so nguyen to nho hon " << M << ": " << primes.size() << endl;
    cout << "Cac so nguyen to: ";
    for (int num : primes) {
        cout << num << " ";
    }
    cout << "\nTong cac so nguyen to: " << sumPrimes << endl;
    
    return 0;
}