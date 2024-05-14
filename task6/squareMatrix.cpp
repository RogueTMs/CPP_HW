#include "squareMatrix.h"
#include <bits/stdc++.h>

SquareMatrix::SquareMatrix(const double_vector &vector) : size_(vector.size()){
    elements_sum_ = std::accumulate(vector.begin(), vector.end(), 0);
    matrix_.resize(size_);
    int counter = 0;
    for (size_t i = 0; i < size_; i++) {
        matrix_[i].resize(size_);
        matrix_[i][counter] = vector[counter];
        counter++;
    }
}

// void SquareMatrix::resize(size_t size) {
//     matrix_.resize(size);
//     for (size_t i = 0; i < size_; i++) {
//         matrix_[i].resize(size, 0);
//     }
// }

size_t SquareMatrix::get_size() const { return size_; }

SquareMatrix::operator double() const { return elements_sum_;};