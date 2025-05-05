#include <iostream>
#include <vector>
#include "Eigen/Dense"  
#include <windows.h>

using namespace std;
using namespace Eigen;

MatrixXd nhapMatran(int n) {
    MatrixXd a(n, n);
    cout << "Nhập ma trận " << n << "x" << n << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Nhập phần tử ở vị trí (" << i + 1 << ", " << j + 1 << "): ";
            cin >> a(i, j);
        }
    }
    return a;
}

void xuatMatran(const MatrixXd& a, const string& name = "Ma trận") {
    cout << name << ":\n";
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < a.cols(); ++j) {
            cout << a(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void phanRaEigen(const MatrixXd& a, VectorXd& eigenvalues, MatrixXd& eigenvectors) {
    EigenSolver<MatrixXd> solver(a);
    eigenvalues = solver.eigenvalues().real();
    eigenvectors = solver.eigenvectors().real();

    cout << "Giá trị riêng (Λ):\n";
    for (int i = 0; i < eigenvalues.size(); ++i) {
        cout << "λ" << i + 1 << " = " << eigenvalues(i) << endl;
    }
    cout << endl;

    cout << "Vector riêng (cột của Q):\n";
    for (int i = 0; i < eigenvectors.cols(); ++i) {
        cout << "v" << i + 1 << " = [";
        for (int j = 0; j < eigenvectors.rows(); ++j) {
            cout << eigenvectors(j, i) << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main() {
	SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);       
    try {
        int n;
        cout << "Nhập kích thước ma trận vuông n = ";
        cin >> n;
        if (n <= 0) {
            throw invalid_argument("Kích thước ma trận phải lớn hơn 0!");
        }

        MatrixXd a = nhapMatran(n);
        xuatMatran(a, "Ma trận đã nhập");

        VectorXd eigenvalues(n);
        MatrixXd eigenvectors(n, n);
        phanRaEigen(a, eigenvalues, eigenvectors);

        MatrixXd Lambda = eigenvalues.asDiagonal();

        MatrixXd Q_inv = eigenvectors.inverse();

        xuatMatran(eigenvectors, "Ma trận vector riêng (Q)");
        xuatMatran(Lambda, "Ma trận giá trị riêng (Λ)");
        xuatMatran(Q_inv, "Ma trận nghịch đảo của vector riêng (Q⁻¹)");

        MatrixXd reconstruct = eigenvectors * Lambda * Q_inv;
        xuatMatran(reconstruct, "Ma trận tái cấu tạo (QΛQ⁻¹)");

        cout << "So sánh với ma trận ban đầu:\n";
        xuatMatran(a, "Ma trận ban đầu");
        xuatMatran(reconstruct, "Ma trận tái cấu tạo");

    } catch (const exception& e) {
        cout << "Lỗi: " << e.what() << endl;
    }

    return 0;
}