#include <iostream>
#include <vector>
#include "../include/Matrix.h"

using namespace std;

void demonstrateBasicOperations() {
    cout << "=== Basic Operations ===" << endl;

    Matrix A({{1, 2, 3},
              {4, 5, 6},
              {7, 8, 9}});

    Matrix B({{9, 8, 7},
              {6, 5, 4},
              {3, 2, 1}});

    cout << "Matrix A:\n" << A << endl;

    cout << "\nMatrix B\n:" << B << endl;

    Matrix C = A + B;

    cout << "\nA + B:\n" << C << endl;

    cout << "\nElement A(1,1) = " << A(1, 1) << endl;
}

void demonstrateTranspose() {
    cout << "\n=== Transpose ===" << endl;

    Matrix M({{1, 2, 3, 4},
              {5, 6, 7, 8}});

    cout << "Matrix M:\n" << M << endl;

    Matrix MT = M.transpose();

    cout << "\nM^T:\n" << MT << endl;
}

void demonstrateMultiplication() {
    cout << "\n=== Multiplication ===" << endl;

    Matrix A({{1, 2},
              {3, 4}});

    Matrix B({{5, 6},
              {7, 8}});

    Matrix C = A * B;

    cout << "A * B:\n" << C << endl;
}

void demonstrateMatrixVector() {
    cout << "\n=== Matrix-Vector ===" << endl;

    Matrix A({{1, 2, 3},
              {4, 5, 6}});

    vector<double> v = {1, 2, 3};

    cout << "Matrix A:\n" << A << endl;

    cout << "\nA * v = ";
    vector<double> result = A * v;
    for (double val : result) {
        cout << val << " ";
    }
    cout << endl;
}

void demonstrateDeterminant() {
    cout << "\n=== Determinant ===" << endl;

    Matrix M2({{3, 8},
               {4, 6}});

    cout << "2x2 matrix:\n" << M2 << endl;

    cout << "det = " << M2.determinant() << endl;

    Matrix M3({{6, 1, 1},
               {4, -2, 5},
               {2, 8, 7}});

    cout << "\n3x3 matrix:\n" << M3 << endl;
    cout << "det = " << M3.determinant() << endl;
}

void demonstrateExceptionHandling() {
    cout << "\n=== Exception Handling ===" << endl;

    try {
        Matrix A(2, 3);
        Matrix B(3, 2);
        Matrix C = A + B;
    } catch (const invalid_argument& e) {
        cout << "Caught: " << e.what() << endl;
    }

    try {
        Matrix M(2, 2);
        double val = M(5, 5);
        (void)val;
    } catch (const out_of_range& e) {
        cout << "Caught: " << e.what() << endl;
    }
}

int main() {
    cout << "\nMatrix Operations Demo\n" << endl;

    try {
        demonstrateBasicOperations();
        demonstrateTranspose();
        demonstrateMultiplication();
        demonstrateMatrixVector();
        demonstrateDeterminant();
        demonstrateExceptionHandling();

        cout << "\nDone!" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
