#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double a, b, c, d; 

void nhapHeSo() {
    cout << "Nhap he so cua ham muc tieu f(x,y) = a*x1^2 + b*x1*x2 + c*x2^2\n";
    cout << "Nhap a = ";
    cin >> a;
    cout << "Nhap b = ";
    cin >> b;
    cout << "Nhap c = ";
    cin >> c;
    cout << "Nhap he so cua ham rang buoc h(x1,x2) = x1 + x2 + d\n";
    cout << "Nhap d = ";
    cin >> d;
}

// Tính f(x1, x2)
double f(double x1, double x2) {
    return a * x1 * x1 + b * x1 * x2 + c * x2 * x2;
}

// Tính h(x1, x2) = x1 + x2 + d
double h(double x1, double x2) {
    return x1 + x2 + d;
}

// Tính x1 theo công thức mẫu (giữ nguyên)
double calc_x1(double lambda, double rk) {
    double num = -90 * rk * rk + 9 * rk * lambda - 6 * lambda + 60 * rk;
    double denom = (14 - 5 * rk) * (12 + 2 * rk);
    return num / denom;
}

// Tính x2 theo công thức mẫu (giữ nguyên)
double calc_x2(double lambda, double rk) {
    double num = 20 * rk - 2 * lambda;
    double denom = 14 - 5 * rk;
    return num / denom;
}

int main() {
    nhapHeSo();

    cout << left << setw(15) << "lambda"
         << setw(15) << "rk"
         << setw(15) << "x1"
         << setw(15) << "x2"
         << setw(15) << "Value of h"
         << endl;

    cout << string(65, '-') << endl;

    double lambda = 0.0;
    double rk = 1.0;

    for (int k = 0; k < 10; ++k) {
        double x1 = calc_x1(lambda, rk);
        double x2 = calc_x2(lambda, rk);
        double hk = h(x1, x2);

        cout << fixed << setprecision(5);
        cout << left << setw(15) << lambda
             << setw(15) << rk
             << setw(15) << x1
             << setw(15) << x2
             << setw(15) << hk << endl;

        if (fabs(hk) < 1e-6) break;

        lambda = lambda + 2 * rk * hk;
    }

    return 0;
}