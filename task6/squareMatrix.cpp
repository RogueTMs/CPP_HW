#include "squareMatrix.h"
#include <bits/stdc++.h>
#include <vector>

SquareMatrix::operator double() const { return elements_sum_; };

SquareMatrix::SquareMatrix(const std::vector<double> &vector){
    shape = vector.size();
    elements_sum_ = std::accumulate(vector.begin(), vector.end(), 0);
    
    matrix_ = new double *[shape];

    for (size_t i = 0; i < shape; i++) {
        matrix_[i] = new double[shape];
        for (size_t j = 0; j < shape; j++) {
            if (i == j)
                matrix_[i][j] = vector.at(i);
            else
                matrix_[i][j] = 0;
        }
    }
}

SquareMatrix::SquareMatrix(double **matrix, size_t shape_) {
    shape = shape_;

    for (size_t i = 0; i < shape; i++) {
        for (size_t j = 0; j < shape; j++) {
            elements_sum_ += matrix_[i][j];
        }
    }
}

double *SquareMatrix::operator[](size_t index) { return matrix_[index]; }

const double *SquareMatrix::operator[](size_t index) const {
    return matrix_[index];
}

SquareMatrix &SquareMatrix::operator=(SquareMatrix other) {
    assert((other.get_shape() == this->shape) &&
           "Sizes of matrices are not equal!");
    std::swap(this->matrix_, other.matrix_);
    std::swap(elements_sum_, other.elements_sum_);
    std::swap(shape, other.shape);
    return *this;
}

bool operator==(const SquareMatrix &first, const SquareMatrix &second) {
    if (first.shape != second.shape) {
        throw std::runtime_error("Different shapes");
    }
    size_t size = first.shape;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (first.matrix_[i][j] != second.matrix_[i][j])
                return false;
        }
    }
    return true;
}

bool operator!=(const SquareMatrix &first, const SquareMatrix &second) {
    return !(first == second);
}

SquareMatrix operator+(const SquareMatrix &first, const SquareMatrix &second) {
    return operation(first, second, [](double a, double b) { return a + b; });
}

SquareMatrix &SquareMatrix::operator-=(const SquareMatrix &other) {
    if (this->shape != other.get_shape()) {
        throw std::runtime_error("Different shapes");
    }
    *this = *this - other;
    return *this;
}

SquareMatrix operator-(const SquareMatrix &first, const SquareMatrix &second) {
    return operation(first, second, [](double a, double b) { return a - b; });
}

SquareMatrix &SquareMatrix::operator*=(const SquareMatrix &other) {
    if (this->shape != other.get_shape()) {
        throw std::runtime_error("Different shapes");
    }
    *this = *this * other;
    return *this;
}

SquareMatrix operator*(const SquareMatrix &first, const SquareMatrix &second) {
    if (first.shape != second.shape) {
        throw std::runtime_error("Different shapes");
    }
    return matmulImpl(first, second);
}

SquareMatrix &SquareMatrix::operator+=(const SquareMatrix &other) {
    if (this->shape != other.get_shape()) {
        throw std::runtime_error("Different shapes");
    }
    *this = *this + other;
    return *this;
}

SquareMatrix operator+(const SquareMatrix &matrix, const double scalar) {
    return matrix + SquareMatrix(std::vector<double>(matrix.get_shape(), scalar));
}

SquareMatrix operator-(const SquareMatrix &matrix, const double scalar) {
    return matrix - SquareMatrix(std::vector<double>(matrix.get_shape(), scalar));
}

SquareMatrix operator*(const SquareMatrix &matrix, const double scalar) {
    return matrix * SquareMatrix(std::vector<double>(matrix.get_shape(), scalar));
}

SquareMatrix operator+(const double scalar, const SquareMatrix &matrix) {
    return SquareMatrix(std::vector<double>(matrix.get_shape(), scalar)) + matrix;
}

SquareMatrix operator-(const double scalar, const SquareMatrix &matrix) {
    return SquareMatrix(std::vector<double>(matrix.get_shape(), scalar)) - matrix;
}

SquareMatrix operator*(const double scalar, const SquareMatrix &matrix) {
    return SquareMatrix(std::vector<double>(matrix.get_shape(), scalar)) * matrix;
}


SquareMatrix &SquareMatrix::operator*=(const double scalar) {
    *this *= SquareMatrix(std::vector<double>(shape, scalar));
    return *this;
}

SquareMatrix &SquareMatrix::operator+=(const double scalar) {
    *this += SquareMatrix(std::vector<double>(shape, scalar));
    return *this;
}

SquareMatrix &SquareMatrix::operator-=(const double scalar) {
    *this -= SquareMatrix(std::vector<double>(shape, scalar));
    return *this;
}

size_t SquareMatrix::get_shape() const { return shape; }

SquareMatrix matmulImpl(const SquareMatrix &first, const SquareMatrix &second) {
    size_t size = first.get_shape();
    SquareMatrix result(size);
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size; ++col) {
            for (size_t inner = 0; inner < size; ++inner) {
                double value = first[row][inner] * second[inner][col];
                result.matrix_[row][col] += value;
                result.elements_sum_ += value;
            }
        }
    }

    return result;
}

SquareMatrix operation(const SquareMatrix &first, const SquareMatrix &second,
                       std::function<double(double, double)> func) {
    size_t size = first.get_shape();
    if (size != second.get_shape()) {
        throw std::runtime_error("Different shapes");
    }

    SquareMatrix result(size);
    for (size_t i = 0; i < result.shape; i++) {
        for (size_t j = 0; j < result.shape; j++) {
            double value = func(first.matrix_[i][j], second.matrix_[i][j]);
            result.elements_sum_ += value - result.matrix_[i][j];
            result.matrix_[i][j] = value;
        }
    }

    return result;
}