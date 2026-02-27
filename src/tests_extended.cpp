#include <iostream>
#include <cassert>
#include <cmath>
#include "../include/Matrix.h"

using namespace std;

int tests_passed = 0;
int tests_failed = 0;

// Tests de base (déjà présents)
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

// ========== TESTS SUPPLÉMENTAIRES ==========

void test_exception_constructor_zero() {
    try {
        Matrix m(0, 5);
        tests_failed++;
        cout << "Test exception constructor zero: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception constructor zero: OK" << endl;
    }
}

void test_exception_addition_mismatch() {
    try {
        Matrix a(2, 3);
        Matrix b(3, 2);
        Matrix c = a + b;
        tests_failed++;
        cout << "Test exception addition mismatch: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception addition mismatch: OK" << endl;
    }
}

void test_exception_mult_mismatch() {
    try {
        Matrix a(2, 3);
        Matrix b(4, 2);
        Matrix c = a * b;
        tests_failed++;
        cout << "Test exception mult mismatch: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception mult mismatch: OK" << endl;
    }
}

void test_exception_matvec_mismatch() {
    try {
        Matrix a(2, 3);
        vector<double> v = {1, 2};  // taille 2, devrait être 3
        vector<double> result = a * v;
        tests_failed++;
        cout << "Test exception matvec mismatch: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception matvec mismatch: OK" << endl;
    }
}

void test_exception_determinant_nonsquare() {
    try {
        Matrix m(2, 3);
        double det = m.determinant();
        (void)det;
        tests_failed++;
        cout << "Test exception determinant nonsquare: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception determinant nonsquare: OK" << endl;
    }
}

void test_exception_out_of_range() {
    try {
        Matrix m(2, 2);
        double val = m(5, 5);
        (void)val;
        tests_failed++;
        cout << "Test exception out_of_range: FAILED (no exception)" << endl;
    } catch (const out_of_range&) {
        tests_passed++;
        cout << "Test exception out_of_range: OK" << endl;
    }
}

void test_determinant_1x1() {
    Matrix m({{5.0}});
    double det = m.determinant();
    assert(abs(det - 5.0) < 1e-9);
    tests_passed++;
    cout << "Test determinant 1x1: OK" << endl;
}

void test_determinant_3x3() {
    Matrix m({{6, 1, 1}, {4, -2, 5}, {2, 8, 7}});
    double det = m.determinant();
    assert(abs(det - (-306.0)) < 1e-9);
    tests_passed++;
    cout << "Test determinant 3x3: OK" << endl;
}

void test_equality_true() {
    Matrix a({{1, 2}, {3, 4}});
    Matrix b({{1, 2}, {3, 4}});
    assert(a == b);
    tests_passed++;
    cout << "Test equality true: OK" << endl;
}

void test_equality_false() {
    Matrix a({{1, 2}, {3, 4}});
    Matrix b({{1, 2}, {3, 5}});
    assert(!(a == b));
    tests_passed++;
    cout << "Test equality false: OK" << endl;
}

void test_exception_constructor_inconsistent() {
    try {
        Matrix m({{1, 2, 3}, {4, 5}});  // lignes de tailles différentes
        tests_failed++;
        cout << "Test exception constructor inconsistent: FAILED (no exception)" << endl;
    } catch (const invalid_argument&) {
        tests_passed++;
        cout << "Test exception constructor inconsistent: OK" << endl;
    }
}

int main() {
    cout << "\n=== Matrix Extended Tests ===\n" << endl;
    
    // Tests de base
    cout << "--- Basic Tests ---" << endl;
    test_constructor();
    test_constructor_values();
    test_element_access();
    test_addition();
    test_multiplication();
    test_transpose();
    test_determinant();
    test_matrix_vector();
    
    // Tests supplémentaires
    cout << "\n--- Exception Tests ---" << endl;
    test_exception_constructor_zero();
    test_exception_addition_mismatch();
    test_exception_mult_mismatch();
    test_exception_matvec_mismatch();
    test_exception_determinant_nonsquare();
    test_exception_out_of_range();
    test_exception_constructor_inconsistent();
    
    cout << "\n--- Extended Tests ---" << endl;
    test_determinant_1x1();
    test_determinant_3x3();
    test_equality_true();
    test_equality_false();
    
    cout << "\n=== Results ===" << endl;
    cout << "✅ Passed: " << tests_passed << endl;
    cout << "❌ Failed: " << tests_failed << endl;
    cout << "📊 Total: " << (tests_passed + tests_failed) << endl;
    
    return tests_failed > 0 ? 1 : 0;
}
