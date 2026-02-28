#include <iostream>
#include <cassert>
#include <cmath>
#include "../include/Matrix.h"

using namespace std;

int tests_passed = 0;
int tests_failed = 0;

void test_constructor() {
    Matrix m(3, 4);
    assert(m.getRows() == 3);
    assert(m.getCols() == 4);
    assert(abs(m(0, 0)) < 1e-9);
    tests_passed++;
    cout << "Test constructor: OK" << endl;
}

void test_constructor_values() {
    Matrix m({{1, 2, 3}, {4, 5, 6}});
    assert(m.getRows() == 2);
    assert(m.getCols() == 3);
    assert(abs(m(0, 0) - 1.0) < 1e-9);
    assert(abs(m(1, 2) - 6.0) < 1e-9);
    tests_passed++;
    cout << "Test constructor with values: OK" << endl;
}

void test_element_access() {
    Matrix m(2, 2);
    m(0, 0) = 1.5;
    m(1, 1) = 2.5;
    assert(abs(m(0, 0) - 1.5) < 1e-9);
    assert(abs(m(1, 1) - 2.5) < 1e-9);
    tests_passed++;
    cout << "Test element access: OK" << endl;
}

void test_addition() {
    Matrix a({{1, 2}, {3, 4}});
    Matrix b({{5, 6}, {7, 8}});
    Matrix c = a + b;
    
    assert(abs(c(0, 0) - 6.0) < 1e-9);
    assert(abs(c(1, 1) - 12.0) < 1e-9);
    tests_passed++;
    cout << "Test addition: OK" << endl;
}

void test_multiplication() {
    Matrix a({{1, 2}, {3, 4}});
    Matrix b({{5, 6}, {7, 8}});
    Matrix c = a * b;
    
    assert(abs(c(0, 0) - 19.0) < 1e-9);
    assert(abs(c(0, 1) - 22.0) < 1e-9);
    assert(abs(c(1, 0) - 43.0) < 1e-9);
    assert(abs(c(1, 1) - 50.0) < 1e-9);
    tests_passed++;
    cout << "Test multiplication: OK" << endl;
}

void test_transpose() {
    Matrix a({{1, 2, 3}, {4, 5, 6}});
    Matrix t = a.transpose();
    
    assert(t.getRows() == 3);
    assert(t.getCols() == 2);
    assert(abs(t(0, 1) - 4.0) < 1e-9);
    tests_passed++;
    cout << "Test transpose: OK" << endl;
}

void test_determinant() {
    Matrix m({{3, 8}, {4, 6}});
    double det = m.determinant();
    assert(abs(det - (-14.0)) < 1e-9);
    tests_passed++;
    cout << "Test determinant: OK" << endl;
}

void test_matrix_vector() {
    Matrix a({{1, 2, 3}, {4, 5, 6}});
    vector<double> v = {1, 2, 3};
    vector<double> result = a * v;
    
    assert(result.size() == 2);
    assert(abs(result[0] - 14.0) < 1e-9);
    assert(abs(result[1] - 32.0) < 1e-9);
    tests_passed++;
    cout << "Test matrix-vector: OK" << endl;
}

void test_exceptions() {
    try {
        Matrix a(2, 3);
        Matrix b(3, 2);
        Matrix c = a + b;
        tests_failed++;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exceptions: OK" << endl;
    }
}

int main() {
    cout << "\n--- Matrix Tests ---\n" << endl;
    
    test_constructor();
    test_constructor_values();
    test_element_access();
    test_addition();
    test_multiplication();
    test_transpose();
    test_determinant();
    test_matrix_vector();
    test_exceptions();
    
    cout << "\nResults: " << tests_passed << " passed, " << tests_failed << " failed\n" << endl;
    
    return tests_failed > 0 ? 1 : 0;
}