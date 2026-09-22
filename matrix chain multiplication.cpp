#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
using namespace std;

int matrixChainMultiplication(const vector<int>& dims) {
    int n = dims.size();
    if (n < 2) {
        throw invalid_argument("At least two dimensions are required.");
    }

    
    vector<vector<int>> m(n, vector<int>(n, 0));

    
    for (int L = 2; L < n; ++L) {
        for (int i = 1; i < n - L + 1; ++i) {
            int j = i + L - 1;
            m[i][j] = numeric_limits<int>::max();

            for (int k = i; k < j; ++k) {

                long long cost = (long long)m[i][k] + m[k + 1][j] +
                                 (long long)dims[i - 1] * dims[k] * dims[j];

                if (cost < m[i][j]) {
                    m[i][j] = (int)cost;
                }
            }
        }
    }
    return m[1][n - 1];
}

int main() {
    int n;
    cout << "Enter number of matrices: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid input. Number of matrices must be positive.\n";
        return 1;
    }

    vector<int> dims(n + 1);
    cout << "Enter dimensions (n+1 integers): ";
    for (int i = 0; i <= n; ++i) {
        if (!(cin >> dims[i]) || dims[i] <= 0) {
            cerr << "Invalid input. Dimensions must be positive integers.\n";
            return 1;
        }
    }

    try {
        int minCost = matrixChainMultiplication(dims);
        cout << "Minimum number of multiplications: " << minCost << "\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
