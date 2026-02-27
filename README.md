# Matrix Operations – Linear Algebra in C++

C++17 implementation of a `Matrix` class providing core linear algebra operations with robust error handling.

---

## Features

- Matrix addition and multiplication  
- Matrix–vector multiplication  
- Transpose  
- Determinant (recursive cofactor expansion, small matrices)  
- Element access via `operator()(i, j)`  
- Exception handling (`std::invalid_argument`, `std::out_of_range`)  
- Floating-point comparison with epsilon (1e-9)  

---

## Project Structure

.
├── include/Matrix.h  
├── src/  
│   ├── Matrix.cpp  
│   ├── main.cpp  
│   ├── examples.cpp  
│   ├── tests.cpp  
│   ├── tests_extended.cpp  
│   └── benchmark.cpp  
├── Makefile  
└── architecture.drawio  

`architecture.drawio` provides a visual overview of the compilation pipeline and data flow.

---

## Compilation

### Using Makefile

```bash
make              # Build project
make run          # Run main demo
make run-examples # Run additional examples
make test         # Run basic test suite (9 tests)
make bench        # Run performance benchmark
make clean        # Remove build files
```

### Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion \
-Iinclude src/Matrix.cpp src/main.cpp -o matrix_program
```

### Extended Tests (19 tests)

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude obj/Matrix.o \
src/tests_extended.cpp -o bin/tests_extended

./bin/tests_extended
```

---

## Implementation Details

- Storage: `std::vector<double>` (row-major layout)  
- Determinant: recursive cofactor expansion  
- Matrix multiplication: optimized i-k-j loop ordering  
- Strict dimension validation  
- Full exception safety for invalid operations  

---

## Validation

- Compiles with strict flags (`-Wall -Wextra -Wpedantic -Wconversion`)  
- C++17 compliant  
- Zero warnings  
- All tests passing  

---

**M2 272 – Université Paris Dauphine**  
C++ Course Project