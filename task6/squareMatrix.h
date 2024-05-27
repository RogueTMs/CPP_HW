#include <cmath>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdio.h>

class SquareMatrix {
    size_t shape = 0;
    double elements_sum_ = 0;
    double **matrix_;

  public:
    SquareMatrix(const std::vector<double> &vector);
    SquareMatrix(double **matrix, size_t shape_);
    SquareMatrix(const size_t shape_) : shape(shape_) {
        matrix_ = new double *[shape];
        for (size_t i = 0; i < shape; i++) {
            matrix_[i] = new double[shape];
            for (size_t j = 0; j < shape; j++) {
                matrix_[i][j] = 0;
            }
        }
    }
    SquareMatrix(const SquareMatrix &other) : SquareMatrix(other.shape) {
        for (size_t i = 0; i < shape; i++) {
            for (size_t j = 0; j < shape; j++) {
                matrix_[i][j] = other.matrix_[i][j];
                elements_sum_ += other.matrix_[i][j];
            }
        }
    }

    SquareMatrix(SquareMatrix &&other)
        : matrix_(std::move(other.matrix_)), shape(other.shape),
          elements_sum_(other.elements_sum_) {
        other.matrix_ = nullptr;
        other.elements_sum_ = 0;
        other.shape = 0;
    }

    double *operator[](size_t index);
    const double *operator[](size_t index) const;

    explicit operator double() const;

    SquareMatrix &operator=(SquareMatrix other);
    friend SquareMatrix operator+(const SquareMatrix &first,
                                  const SquareMatrix &second);
    friend SquareMatrix operator-(const SquareMatrix &first,
                                  const SquareMatrix &second);
    friend SquareMatrix operator*(const SquareMatrix &first,
                                  const SquareMatrix &second);
    SquareMatrix &operator+=(const SquareMatrix &other);
    SquareMatrix &operator-=(const SquareMatrix &other);
    SquareMatrix &operator*=(const SquareMatrix &other);

    friend bool operator==(const SquareMatrix &first,
                           const SquareMatrix &second);
    friend bool operator!=(const SquareMatrix &first,
                           const SquareMatrix &second);

    friend SquareMatrix operator+(const SquareMatrix &matrix,
                                  const double scalar);
    friend SquareMatrix operator-(const SquareMatrix &matrix,
                                  const double scalar);
    friend SquareMatrix operator*(const SquareMatrix &matrix,
                                  const double scalar);
    friend SquareMatrix operator+(const double scalar,
                                  const SquareMatrix &matrix);
    friend SquareMatrix operator-(const double scalar,
                                  const SquareMatrix &matrix);
    friend SquareMatrix operator*(const double scalar,
                                  const SquareMatrix &matrix);

    SquareMatrix &operator+=(const double scalar);
    SquareMatrix &operator-=(const double scalar);
    SquareMatrix &operator*=(const double scalar);

    ~SquareMatrix() {
        if (matrix_) {
            for (size_t i = 0; i < shape; i++) {
                delete[] matrix_[i];
            }
        }
        delete[] matrix_;
    }

    size_t get_shape() const;

  private:
    friend SquareMatrix matmulImpl(const SquareMatrix &first,
                                   const SquareMatrix &second);
    friend SquareMatrix operation(const SquareMatrix &first,
                                  const SquareMatrix &second,
                                  std::function<double(double, double)> func);
};