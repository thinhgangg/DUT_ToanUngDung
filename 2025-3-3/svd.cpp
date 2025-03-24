#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
    Eigen::Matrix3f A;
    cout << "Enter matrix 3x3: " << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> A(i, j);
        }
    }
    Eigen::Matrix3f S = A.transpose() * A;
    cout << "S: " << endl
         << S << endl;
    Eigen::EigenSolver<Eigen::Matrix3f> solver(S);
    Eigen::Vector3f eigenValues = solver.eigenvalues().real();
    Eigen::Matrix3f eigenVectors = solver.eigenvectors().real();
    cout << "Eigen values: " << endl
         << eigenValues << endl;
    cout << "Eigen vectors: " << endl
         << eigenVectors << endl;
    Eigen::Matrix3f Sig, VT = eigenVectors.transpose(), U = A * eigenVectors;
    for (int i = 0; i < 3; ++i)
    {
        Sig(i, i) = sqrt(eigenValues[i]);
        for (int j = 0; j < 3; ++j)
        {
            U(j, i) /= Sig(i, i);
            if (j != i)
                Sig(j, i) = 0;
        }
    }
    cout << "U: " << endl
         << U << endl;
    cout << "Sig: " << endl
         << Sig << endl;
    cout << "VT: " << endl
         << VT << endl;
    cout << "U * Sig * VT: " << endl
         << U * Sig * VT << endl;
    return 0;
}