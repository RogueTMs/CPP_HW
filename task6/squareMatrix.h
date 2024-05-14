#include <functional>
#include <iostream>
#include <optional>
#include <sstream>

typedef std::vector<double> double_vector;

class SquareMatrix {
    size_t size_ = 0;
    double elements_sum_ = 0;
    std::vector<double_vector> matrix_;

  public:
    SquareMatrix(const double_vector &vector);
    SquareMatrix(const size_t &size) : size_(size) { resize(size_); }
    SquareMatrix(const SquareMatrix &other)
        : matrix_(other.matrix_), size_(other.size_),
          elements_sum_(other.elements_sum_) {}

    SquareMatrix(SquareMatrix &&other)
        : matrix_(std::move(other.matrix_)), size_(other.size_),
          elements_sum_(other.elements_sum_) {
        other.elements_sum_ = 0;
        other.size_ = 0;
    }

    double_vector &operator[](size_t index);
    const double_vector &operator[](size_t index) const;

    explicit operator double() const;

    SquareMatrix &operator=(SquareMatrix other);
    friend SquareMatrix operator+(const SquareMatrix &first,
                                  const SquareMatrix &second);
    friend SquareMatrix operator-(const SquareMatrix &first,
                                  const SquareMatrix &second);
    friend SquareMatrix operator*(const SquareMatrix &first,
                                  const SquareMatrix &second);
    SquareMatrix &operator+=(const SquareMatrix &other);
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
    SquareMatrix &operator+=(const double scalar);
    SquareMatrix &operator*=(const double scalar);

    ~SquareMatrix() = default;

    friend void print_matrix(const SquareMatrix &matrix);
    size_t get_size() const;

  private:
    void resize(size_t size);
    friend SquareMatrix matrix_mult(const SquareMatrix &first,
                                    const SquareMatrix &second);
    friend SquareMatrix apply(const SquareMatrix &first,
                              const SquareMatrix &second,
                              std::function<double(double, double)> func);
};