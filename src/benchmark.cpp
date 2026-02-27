#include <iostream>
#include <chrono>
#include <iomanip>
#include <functional>
#include "../include/Matrix.h"

using namespace std;
using namespace std::chrono;

// Runs a function N times and returns average duration in microseconds
double measure_us(int N, function<void()> fn) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) fn();
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count() / 1000.0 / N;
}

// Fills a matrix with arbitrary values to avoid optimizer elision
Matrix make_filled(size_t n) {
    Matrix m(n, n);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            m(i, j) = static_cast<double>(i * n + j + 1);
    return m;
}

void print_header(const string& title) {
    cout << "\n=== " << title << " ===\n";
    cout << left << setw(10) << "Size"
         << right << setw(16) << "Avg time (us)"
         << "\n";
    cout << string(26, '-') << "\n";
}

void print_row(const string& label, double us) {
    cout << left << setw(10) << label
         << right << setw(14) << fixed << setprecision(2) << us << " us\n";
}

// ------------------- Benchmarks -------------------

void bench_addition() {
    print_header("Matrix Addition (A + B)");
    for (size_t n : {10, 50, 100, 200, 500}) {
        Matrix A = make_filled(n);
        Matrix B = make_filled(n);
        int N = (n <= 100) ? 1000 : 100;
        double us = measure_us(N, [&]() {
            Matrix C = A + B;
            (void)C;
        });
        print_row(to_string(n) + "x" + to_string(n), us);
    }
}

void bench_matmul() {
    print_header("Matrix Multiplication (A * B)");
    for (size_t n : {10, 50, 100, 200}) {
        Matrix A = make_filled(n);
        Matrix B = make_filled(n);
        int N = (n <= 50) ? 500 : (n <= 100 ? 50 : 5);
        double us = measure_us(N, [&]() {
            Matrix C = A * B;
            (void)C;
        });
        print_row(to_string(n) + "x" + to_string(n), us);
    }
}

void bench_matvec() {
    print_header("Matrix-Vector Multiplication (A * v)");
    for (size_t n : {10, 50, 100, 200, 500}) {
        Matrix A = make_filled(n);
        vector<double> v(n, 1.0);
        int N = (n <= 100) ? 1000 : 200;
        double us = measure_us(N, [&]() {
            vector<double> r = A * v;
            (void)r;
        });
        print_row(to_string(n) + "x" + to_string(n), us);
    }
}

void bench_transpose() {
    print_header("Transpose");
    for (size_t n : {10, 50, 100, 200, 500}) {
        Matrix A = make_filled(n);
        int N = (n <= 100) ? 1000 : 100;
        double us = measure_us(N, [&]() {
            Matrix T = A.transpose();
            (void)T;
        });
        print_row(to_string(n) + "x" + to_string(n), us);
    }
}

void bench_determinant() {
    print_header("Determinant (cofactor expansion)");
    for (size_t n : {1, 2, 3, 4, 5, 6, 7, 8}) {
        Matrix A = make_filled(n);
        int N = (n <= 5) ? 10000 : (n <= 7 ? 100 : 10);
        double us = measure_us(N, [&]() {
            double d = A.determinant();
            (void)d;
        });
        print_row(to_string(n) + "x" + to_string(n), us);
    }
    cout << "  (cofactor expansion: O(n!) complexity)\n";
}

// --------------------------------------------------

int main() {
    cout << "\n========================================\n";
    cout << "   Matrix Operations - Benchmark\n";
    cout << "========================================\n";

    bench_addition();
    bench_matmul();
    bench_matvec();
    bench_transpose();
    bench_determinant();

    cout << "\nDone.\n";
    return 0;
}
