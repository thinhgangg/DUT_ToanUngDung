#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

void choleskyDecomposition(int n, double** a, double** L, double** D) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = 0;
            D[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            if (i == j) {
                for (int k = 0; k < j; k++) {
                    sum += L[j][k] * L[j][k] * D[k][k];
                }
                D[j][j] = a[j][j] - sum;
                L[j][j] = 1;
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k] * D[k][k];
                }
                L[i][j] = (a[i][j] - sum) / D[j][j];
            }
        }
    }
}

void printMatrix(int n, double** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void checking(int n, double** a, double** L, double** D, double** U) {
    double** result = new double*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new double[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += L[i][k] * D[k][k] * U[k][j];
            }
        }
    }
    cout << "Ma tran A = L * D * L^-1: " << endl;
    printMatrix(n, result);

    for (int i = 0; i < n; i++) {
        delete[] result[i];
    }
    delete[] result;
}

int main() {
    int n = 3;
    double** a = new double*[n];
    a[0] = new double[n]{4, 12, -16};
    a[1] = new double[n]{12, 37, -43};
    a[2] = new double[n]{-16, -43, 98};

    double** L = new double*[n];
    double** D = new double*[n];
    double** U = new double*[n];
    for (int i = 0; i < n; i++) {
        L[i] = new double[n];
        D[i] = new double[n];
        U[i] = new double[n];
    }
    

    choleskyDecomposition(n, a, L, D);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            U[i][j] = L[j][i];
        }
    }
    cout << "Ma tran A:" << endl;
    printMatrix(n, a);
    cout << "Ma tran L:" << endl;
    printMatrix(n, L);
    cout << "Ma tran D:" << endl;
    printMatrix(n, D);
    cout << "Ma tran L^-1:" << endl;
    printMatrix(n, U);

    checking(n, a, L, D, U);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
        delete[] L[i];
        delete[] D[i];
        delete[] U[i];
    }
    delete[] a;
    delete[] L;
    delete[] D;
    delete[] U;
    return 0;
}