# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET_MAIN = $(BIN_DIR)/matrix_program
TARGET_EXAMPLES = $(BIN_DIR)/examples
TARGET_TESTS = $(BIN_DIR)/tests
TARGET_BENCH = $(BIN_DIR)/benchmark

OBJ_MATRIX = $(OBJ_DIR)/Matrix.o

all: $(TARGET_MAIN) $(TARGET_EXAMPLES) $(TARGET_TESTS) $(TARGET_BENCH)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_MATRIX): $(SRC_DIR)/Matrix.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_MAIN): $(OBJ_MATRIX) $(SRC_DIR)/main.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_MATRIX) $(SRC_DIR)/main.cpp -o $(TARGET_MAIN)

$(TARGET_EXAMPLES): $(OBJ_MATRIX) $(SRC_DIR)/examples.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_MATRIX) $(SRC_DIR)/examples.cpp -o $(TARGET_EXAMPLES)

$(TARGET_TESTS): $(OBJ_MATRIX) $(SRC_DIR)/tests.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_MATRIX) $(SRC_DIR)/tests.cpp -o $(TARGET_TESTS)

$(TARGET_BENCH): $(OBJ_MATRIX) $(SRC_DIR)/benchmark.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -O2 $(OBJ_MATRIX) $(SRC_DIR)/benchmark.cpp -o $(TARGET_BENCH)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

run-examples: $(TARGET_EXAMPLES)
	./$(TARGET_EXAMPLES)

test: $(TARGET_TESTS)
	./$(TARGET_TESTS)

bench: $(TARGET_BENCH)
	./$(TARGET_BENCH)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run run-examples test bench clean