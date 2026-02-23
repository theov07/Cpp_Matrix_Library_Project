#include "../include/Matrix.h"
#include <iomanip>
#include <cmath>

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    if (rows == 0 || cols == 0) {
        throw std::invalid_argument("Matrix dimensions must be greater than zero");
    }
    data.resize(rows * cols, 0.0);
}

Matrix::Matrix(const std::vector<std::vector<double>>& values) {
    if (values.empty() || values[0].empty()) {
        throw std::invalid_argument("Cannot create matrix from empty vector");
    }
    
    rows = values.size();
    cols = values[0].size();
    
    for (const auto& row : values) {
        if (row.size() != cols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }
    
    data.reserve(rows * cols);
    for (const auto& row : values) {
        for (double val : row) {
            data.push_back(val);
        }
    }
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getCols() const {
    return cols;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data[i * cols + j];
}

double& Matrix::operator()(size_t i, size_t j) {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data[i * cols + j];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication");
    }
    
    Matrix result(rows, other.cols);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < cols; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    
    return result;
}

std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
    if (cols != vec.size()) {
        throw std::invalid_argument("Vector size must match number of matrix columns");
    }
    
    std::vector<double> result(rows, 0.0);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += (*this)(i, j) * vec[j];
        }
    }
    
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    
    const double epsilon = 1e-9;
    for (size_t i = 0; i < data.size(); ++i) {
        if (std::abs(data[i] - other.data[i]) > epsilon) {
            return false;
        }
    }
    
    return true;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    
    return result;
}

double Matrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant can only be calculated for square matrices");
    }
    
    // Convert to 2D vector for calculation
    std::vector<std::vector<double>> mat(rows, std::vector<double>(cols));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat[i][j] = (*this)(i, j);
        }
    }
    
    return calculateDeterminant(mat, rows);
}

void Matrix::print(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < rows; ++i) {
        os << "[ ";
        for (size_t j = 0; j < cols; ++j) {
            os << std::setw(8) << (*this)(i, j);
            if (j < cols - 1) os << " ";
        }
        os << " ]" << std::endl;
    }
}

double Matrix::calculateDeterminant(const std::vector<std::vector<double>>& mat, size_t n) const {
    if (n == 1) {
        return mat[0][0];
    }
    
    if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    
    // Cofactor expansion along first row
    double det = 0.0;
    for (size_t j = 0; j < n; ++j) {
        std::vector<std::vector<double>> submat = getSubmatrix(mat, 0, j, n);
        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * mat[0][j] * calculateDeterminant(submat, n - 1);
    }
    
    return det;
}

std::vector<std::vector<double>> Matrix::getSubmatrix(
    const std::vector<std::vector<double>>& mat, 
    size_t excludeRow, 
    size_t excludeCol, 
    size_t n) const {
    
    std::vector<std::vector<double>> submat(n - 1, std::vector<double>(n - 1));
    
    size_t subi = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i == excludeRow) continue;
        
        size_t subj = 0;
        for (size_t j = 0; j < n; ++j) {
            if (j == excludeCol) continue;
            
            submat[subi][subj] = mat[i][j];
            ++subj;
        }
        ++subi;
    }
    
    return submat;
}
