#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
#include <iostream>

// Matrix class for linear algebra operations
class Matrix {
private:
    std::vector<double> data;
    size_t rows;
    size_t cols;

public:
    // Constructors
    Matrix(size_t rows, size_t cols);
    Matrix(const std::vector<std::vector<double>>& values);

    // Accessors
    size_t getRows() const;
    size_t getCols() const;

    // Element access
    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);

    // Matrix operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    std::vector<double> operator*(const std::vector<double>& vec) const;
    bool operator==(const Matrix& other) const;
    
    Matrix transpose() const;
    double determinant() const;
    void print(std::ostream& os = std::cout) const;

private:
    // Helper functions for determinant
    double calculateDeterminant(const std::vector<std::vector<double>>& mat, size_t n) const;
    std::vector<std::vector<double>> getSubmatrix(
        const std::vector<std::vector<double>>& mat, 
        size_t excludeRow, 
        size_t excludeCol, 
        size_t n) const;
};

#endif
