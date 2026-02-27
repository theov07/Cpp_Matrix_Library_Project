#include <iostream>
#include "../include/Matrix.h"

using namespace std;

void example_identity_matrix() {
    cout << "Identity Matrix" << endl;

    Matrix I({{1, 0, 0},
              {0, 1, 0},
              {0, 0, 1}});

    Matrix A({{2, 3, 1},
              {4, 5, 2},
              {1, 1, 1}});

    cout << "Matrix A:\n" << A << endl;

    Matrix result = A * I;

    cout << "\nA * I:\n" << result << endl;

    cout << "\nA == (A * I): " << (A == result ? "true" : "false") << endl;
}

void example_symmetric_matrix() {
    cout << "\nSymmetric Matrix" << endl;

    Matrix S({{1, 2, 3},
              {2, 4, 5},
              {3, 5, 6}});

    cout << "Matrix S:\n" << S << endl;

    Matrix ST = S.transpose();

    cout << "\nS^T:\n" << ST << endl;

    cout << "\nS == S^T: " << (S == ST ? "true" : "false") << endl;
}

void example_matrix_powers() {
    cout << "\nMatrix Powers" << endl;

    Matrix A({{1, 1},
              {0, 1}});

    cout << "A:\n" << A << endl;

    Matrix A2 = A * A;
    cout << "\nA^2:\n" << A2 << endl;

    Matrix A3 = A2 * A;
    cout << "\nA^3:\n" << A3 << endl;
}

void example_determinant_properties() {
    cout << "\nDeterminant Properties" << endl;

    Matrix A({{2, 3},
              {1, 4}});

    Matrix B({{5, 6},
              {7, 8}});

    cout << "det(A) = " << A.determinant() << endl;
    cout << "det(B) = " << B.determinant() << endl;

    Matrix AB = A * B;
    cout << "det(A*B) = " << AB.determinant() << endl;
    cout << "det(A) * det(B) = " << (A.determinant() * B.determinant()) << endl;
}

int main() {
    cout << "\nMatrix Examples\n" << endl;

    try {
        example_identity_matrix();
        example_symmetric_matrix();
        example_matrix_powers();
        example_determinant_properties();

        cout << "\nDone!" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
