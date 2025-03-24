#include<iostream>
#include<cmath>
using namespace std;

void choleskyDecomposition(int n, double** a, double** lower){ 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            lower[i][j] = 0;
        }
    } 
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= i; j++) {
            double sum = 0;

            if (i == j) {
                for (int k = 0; k < j; k++){
                    sum += pow(lower[i][k], 2);
                }
                lower[i][j] = sqrt(a[i][j] - sum);
            } else {
                for (int k = 0; k < j; k++){
                    sum += (lower[i][k] * lower[j][k]);
                }
                lower[i][j] = (a[i][j] - sum) / lower[j][j];
            }
        }
    }
}

void checking(int n, double** a, double** lower, double** upper){
    double** result = new double*[n];
    for (int i = 0; i < n; i++){
        result[i] = new double[n];
        for (int j = 0; j < n; j++){
            result[i][j] = 0;
            for (int k = 0; k < n; k++){
                result[i][j] += lower[i][k] * upper[k][j];
            }
        }
    }
    cout << "Ma tran A = L * L^-1: " << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        delete[] result[i];
    }
    delete[] result;
}

void printArr(int n, double** a){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int n = 3; 
    //cout << "Nhap n: "; cin >> n; 
    double** a = new double*[n];
    a[0] = new double[n]{4, 12, -16};
    a[1] = new double[n]{12, 37, -43};
    a[2] = new double[n]{-16, -43, 98};

    double** lower = new double*[n];
    double** upper = new double*[n];
    for (int i = 0; i < n; i++) {
        lower[i] = new double[n];
        upper[i] = new double[n];
    }

    choleskyDecomposition(n, a, lower);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            upper[i][j] = lower[j][i];
        }
    }

    cout << "Ma tran A: " << endl;
    printArr(n, a);
    cout << "Ma tran L: " << endl;
    printArr(n, lower);
    cout << "Ma tran L^-1: " << endl;
    printArr(n, upper);
    checking(n, a, lower, upper);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
        delete[] lower[i];
        delete[] upper[i];
    }
    delete[] a;
    delete[] lower;
    delete[] upper;

    return 0;
}