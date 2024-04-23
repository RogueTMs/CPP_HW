// SquareMatrix.cpp
#include "SquareMatrix.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

// Existing constructor
SquareMatrix::SquareMatrix(size_t size) : size(size), matrix(size, std::vector<double>(size, 0.0)) {}

// New constructor from a 1D vector of doubles
SquareMatrix::SquareMatrix(const std::vector<double>& values) {
    size = std::sqrt(values.size());
    if (size * size != values.size()) {
        throw std::invalid_argument("The number of elements is not a perfect square");
    }
    matrix.resize(size);
    for (size_t row = 0; row < size; ++row) {
        matrix[row].resize(size);
        for (size_t col = 0; col < size; ++col) {
            matrix[row][col] = values[row * size + col];
        }
    }
}

// Set value at given row and column
void SquareMatrix::set(size_t row, size_t col, double value) {
    // Implementation remains the same, just ensure using double
}

// Get value at given row and column
double SquareMatrix::get(size_t row, size_t col) const {
    // Implementation remains the same, just ensure using double
}

// Print the matrix
void SquareMatrix::print() const {
    for (const auto &row : matrix) {
        for (double val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}

double SquareMatrix::determinant() const {
    if (size == 1) {
        return matrix[0][0];
    } else if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        double det = 0.0;
        int sign = 1;
        for (size_t i = 0; i < size; i++) {
            SquareMatrix subMatrix(size - 1);
            for (size_t j = 1; j < size; j++) {
                size_t subi = 0;
                for (size_t k = 0; k < size; k++) {
                    if (k == i) continue;
                    subMatrix.set(j - 1, subi, matrix[j][k]);
                    subi++;
                }
            }
            det += sign * matrix[0][i] * subMatrix.determinant();
            sign = -sign;
        }
        return det;
    }
}