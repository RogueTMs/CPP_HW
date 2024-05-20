#include "squareMatrix.h"
#include <bits/stdc++.h>

SquareMatrix::operator double() const { return elements_sum_;};

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

double_vector& SquareMatrix::operator[](size_t index){
    return matrix_[index];
}

const double_vector& SquareMatrix::operator[](size_t index) const{
    return matrix_[index];
}

SquareMatrix& SquareMatrix::operator=(SquareMatrix other){
    assert((other.get_size() == this->size_) && "Sizes of matrices are not equal!");
    std::swap(this->matrix_, other.matrix_);
    std::swap(elements_sum_, other.elements_sum_);
    std::swap(size_, other.size_);
    return *this;
 }

bool operator==(const SquareMatrix& first, const SquareMatrix& second) {
    if (first.size_ != second.size_){
        throw std::runtime_error("Different shapes");
    }
    size_t size = first.size_;
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j < size; j++){
            if (first.matrix_[i][j] != second.matrix_[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const SquareMatrix& first, const SquareMatrix& second) {
    return !(first == second);
}



SquareMatrix operator+(const SquareMatrix& first, const SquareMatrix& second){
    return operation(first, second, [](double a, double b){return a + b;});
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix &other){
    if (this->size_ != other.get_size()){
        throw std::runtime_error("Different shapes");
    }
    *this = *this - other;
    return *this;
}

SquareMatrix operator-(const SquareMatrix& first, const SquareMatrix& second){
    return operation(first, second, [](double a, double b){return a - b;});
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix &other){
    if (this->size_ != other.get_size()){
        throw std::runtime_error("Different shapes");
    }
    *this = *this * other;
    return *this;
}

SquareMatrix operator*(const SquareMatrix& first, const SquareMatrix& second){
    if (first.size_ != second.size_){
        throw std::runtime_error("Different shapes");
    }
    return matmulImpl(first, second);
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix &other){
    if (this->size_ != other.get_size()){
        throw std::runtime_error("Different shapes");
    }
    *this = *this + other;
    return *this;
}

SquareMatrix operator+(const SquareMatrix& matrix, const double scalar){
    return matrix + double_vector(matrix.size_, scalar);
}

SquareMatrix operator-(const SquareMatrix& matrix, const double scalar){
    return matrix - double_vector(matrix.size_, scalar);
}

SquareMatrix operator*(const SquareMatrix& matrix, const double scalar){
    return matrix * double_vector(matrix.size_, scalar);
}

SquareMatrix& SquareMatrix::operator*=(const double scalar){
    *this *= double_vector(size_, scalar);
    return *this;
}

SquareMatrix& SquareMatrix::operator+=(const double scalar){
    *this += double_vector(size_, scalar);
    return *this;
}

SquareMatrix& SquareMatrix::operator-=(const double scalar){
    *this -= double_vector(size_, scalar);
    return *this;
}

size_t SquareMatrix::get_size() const { return size_; }

SquareMatrix matmulImpl(const SquareMatrix &first, const SquareMatrix &second){
    size_t size = first.get_size();
    SquareMatrix result(size);
    for (size_t row = 0; row < size; ++row){
        for (size_t col = 0; col < size; ++col){
            for (size_t inner = 0; inner < size; ++inner){
                double value = first[row][inner] * second[inner][col];
                result.matrix_[row][col] += value;
                result.elements_sum_ += value;
            }
        }
    }

    return result;
}

SquareMatrix operation(const SquareMatrix &first, const SquareMatrix &second, std::function<double(double, double)> func){
    size_t size = first.get_size();
    if (size != second.get_size()){
        throw std::runtime_error("Different shapes");
    }

    SquareMatrix result(size);
        for(size_t i = 0; i < result.size_; i++) {
            for(size_t j = 0; j < result.size_; j++){
                double value = func(first.matrix_[i][j], second.matrix_[i][j]);
                result.elements_sum_ += value - result.matrix_[i][j];
                result.matrix_[i][j] = value;
            }
    }

    return result;

}