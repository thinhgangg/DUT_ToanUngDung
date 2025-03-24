// Chinese remainder theorem

#include <iostream>
#include <vector>
using namespace std;

void Input(vector <int> &a, vector <int> &m, const int &n) {
    a.resize(n);
    m.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "a" << i + 1 << " = ";
        cin >> a[i];
        cout << "m" << i + 1 << " = ";
        cin >> m[i];
        
    }
}

int ChineseRemainderTheorem(const vector <int> &a, const vector <int> &m, const vector <int> &y) {
    int result = 0;
    for (int i = 0; i < a.size(); i++) {
        result += a[i] *m[i] * y[i];
    }
    return result;
}

int main() {
    int n;
    cout << "n = ";
    cin >> n;

    vector<int> a, m;
    Input(a, m, n);

    int MM = 1;
    for (int i = 0; i < m.size(); i++) {
        MM *= m[i];
    }

    vector<int> M(n);
    for (int i = 0; i < m.size(); i++) {
        M[i] = MM / m[i];
    }

    vector <int> y(n);
    for (int i = 0; i < m.size(); i++) {
        y[i] = M[i] % m[i];
    }
    
    cout << ChineseRemainderTheorem(a, M, y);

    return 0;
}