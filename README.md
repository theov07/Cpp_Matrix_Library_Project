# Matrix Operations - Linear Algebra in C++

Implementation of a Matrix class for basic linear algebra operations.

## What it does

- Matrix addition and multiplication
- Matrix-vector multiplication  
- Transpose
- Determinant (for small matrices)
- Element access with operator()
- Exception handling for dimension errors

## Structure

```
.
├── include/Matrix.h      # Class definition
├── src/
│   ├── Matrix.cpp        # Implementation
│   ├── main.cpp          # Main demo
│   ├── examples.cpp      # More examples
│   └── tests.cpp         # Unit tests
├── Makefile             # Build config
└── architecture.drawio  # Project architecture diagram
```

See `architecture.drawio` for a visual overview of the compilation pipeline and data flow.

## Compilation

```bash
make              # Build everything
make run          # Run main program
make run-examples # Run examples
make test         # Run tests
make clean        # Clean build files
```

Or manually:
```bash
g++ -std=c++17 -Iinclude src/Matrix.cpp src/main.cpp -o matrix_program
```

## Usage

```cpp
Matrix A({{1, 2}, {3, 4}});
Matrix B({{5, 6}, {7, 8}});

Matrix C = A + B;              // Addition
Matrix D = A * B;              // Multiplication
Matrix T = A.transpose();      // Transpose
double det = A.determinant();  // Determinant

A(0, 1) = 10;                  // Set element
double val = A(0, 1);          // Get element
```

## Implementation notes

- Data stored in `std::vector<double>` (row-major)
- Determinant uses cofactor expansion (recursive)
- Exceptions for dimension mismatches and out of bounds access

---

M2 272 Dauphine - C++ Course Project