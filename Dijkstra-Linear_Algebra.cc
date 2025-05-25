#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;
typedef vector<vector<double>> Matrix;
const double m = numeric_limits<double>::max();

void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            if (val == m)
                cout << "∞\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty() || A[0].empty() || B[0].empty()) {
        throw invalid_argument("Input matrices cannot be empty.");
    }

    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw invalid_argument("Number of columns in A must equal number of rows in B.");
    }

    Matrix C(rowsA, vector<double>(colsB, m));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            double minim = m;
            for (int k = 0; k < colsA; ++k) {
                if (A[i][k] != m && B[k][j] != m)
                    minim = min(minim, A[i][k] + B[k][j]);
            }
            if (i == j)
                C[i][j] = 0;
            else
                C[i][j] = minim;
        }
    }

    return C;
}

int main() {
    Matrix A = {
        {m, 2, 1, m, 3},
        {m, m, m, 4, m},
        {m, 1, m, m, 1},
        {1, m, 3, m, 5},
        {m, m, m, m, m}
    };

    cout << "Graph:" << endl;
    printMatrix(A);

    Matrix Ai = A;
    for (int i = 1; i < 4; i++) {
        Ai = multiplyMatrices(Ai, A);
        cout << "\nResult of A :-) " << i << ": " << endl;
        printMatrix(Ai);
    }

    return 0;
}
