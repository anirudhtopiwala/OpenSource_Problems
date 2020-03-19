/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 */
#include <iostream>
#include <vector>
// Matrix Class Implementation
template <typename T>
class Matrix {
 private:
  std::vector<std::vector<T>> _mat;
  std::pair<size_t, size_t> _dimension;

 public:
  /**
   * @brief Constructor for an an empty Matrix object
   *
   */
  Matrix() noexcept;
  /**
   * @brief Constructor for a Matrix object with user given rows and cols and
   * initialized to user given value.
   *
   * @param[in] rows
   * @param[in] cols
   * @param[in] val
   */
  Matrix(const size_t rows, const size_t cols, const T val) noexcept;
  /**
   * @brief Constructor for a Matrix object with user given rows and cols and
   * initialized to user given vector of values. The values are filled
   * row wise.
   *
   * @param[in] rows
   * @param[in] cols
   * @param[in] val_vector
   */
  Matrix(const size_t rows, const size_t cols, const std::vector<T> val_vector);

  /**
   * @brief Copy Constructor
   *
   * @param[in] other
   */
  Matrix(const Matrix& other) noexcept;
  /**
   * @brief Move Constructor
   *
   * @param[in] other
   */
  Matrix(const Matrix&& other) noexcept;

  /**
   * @brief Copy Assignment Operator
   *
   * @param[in] other
   * @return Matrix&
   */
  Matrix& operator=(const Matrix& other) noexcept;

  /**
   * @brief Move Assignment Operator
   *
   * @param[in] other
   * @return Matrix&
   */
  Matrix& operator=(const Matrix&& other) noexcept;
  /**
   * @brief Get the Dimension of the matrix
   *
   * @return The dimension of the matrix by reference
   */
  std::pair<size_t, size_t>& GetDimension() const;
  /**
   * @brief Print the Values of the Matrix
   *
   */
  void Print() const;
  /**
   * @brief Change the Values of Matrix by indexing
   *
   * @param[in] row
   * @param[in] col
   * @param[in] val
   */
  void IndexAssign(const size_t row, const size_t col, const T val);
  /**
   * @brief Get the Transpose of the Matrix
   *
   * @return Return a new Matrix object which is the transpose of original
   * Matrix
   */
  Matrix<T> Transpose() const;
  /**
   * @brief Overloaded Multiplication Operator for Matrix Multiplication
   *
   * @param[in] rhs
   * @return Return a new Matrix object which is the Multiplication of the
   * current matrix object and the input Matrix object. If dimensions are
   * incompatible, it return a zero initialalized Matrix object.
   */
  // Overloaded Operators
  Matrix<T> operator*(const Matrix<T>& rhs) const;
  /**
   * @brief Overloaded Multiplication Operator for Scalar Multiplication with
   * Matrix
   *
   * @param[in] rhs
   * @return Return a new Matrix object which is the Multiplication of the
   * current matrix object and the input scalar.
   */
  Matrix<T> operator*(const T scalar) const;
  /**
   * @brief Overloaded Division Operator for Scalar Division with Matrix
   *
   * @param[in] scalar
   * @return Return a new Matrix object which is the Division of the
   * current matrix object and the input scalar.
   */
  Matrix<T> operator/(const T scalar) const;
  /**
   * @brief Overloaded Addition operation with Matrix
   *
   * @param[in] rhs
   * @return Return a new Matrix object which is the Addition of the
   * current matrix object and the input Matrix object. If dimensions are
   * incompatible, returns zero initialized Matrix.
   */
  Matrix<T> operator+(const Matrix<T>& rhs) const;
  /**
   * @brief Overloaded Addition operation with Scalar
   *
   * @param[in] scalar
   * @return Return a new Matrix object which is the Addition of the
   * current matrix object and the input scalar.
   */
  Matrix<T> operator+(const T scalar) const;
  /**
   * @brief Overloaded Subtraction operation with Matrix
   *
   * @param[in] rhs
   * @return Return a new Matrix object which is the Subtraction of the
   * current matrix object and the input Matrix object. If dimensions are
   * incompatible, returns zero initialized Matrix.
   */
  Matrix<T> operator-(const Matrix<T>& rhs) const;
  /**
   * @brief Overloaded Subtraction operation with Scalar
   *
   * @param[in] scalar
   * @return Return a new Matrix object which is the Subtraction of the
   * current matrix object and the input scalar.
   */
  Matrix<T> operator-(const T scalar) const;
};

template <typename T>
Matrix<T>::Matrix() noexcept : _dimension(std::make_pair(0, 0)) {
  T init_val{};
  _mat.assign(0, std::vector<T>(0, init_val));
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T val) noexcept
    : _dimension(std::make_pair(rows, cols)) {
  _mat.assign(rows, std::vector<T>(cols, val));
  _dimension = std::make_pair(rows, cols);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, std::vector<T> val_vector)
    : _dimension(std::make_pair(rows, cols)) {
  T init_val{};
  _mat.assign(rows, std::vector<T>(cols, init_val));
  if (rows * cols == val_vector.size()) {
    size_t k = 0;
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        _mat[i][j] = val_vector[k++];
      }
    }
  } else {
    std::cout << "Incorrect vector inputs, initializing to zero matrix"
              << std::endl;
  }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) noexcept : _dimension(other._dimension) {
  _mat = other._mat;
  std::cout << "Inside the Copy Constructor" << std::endl;
}

template <typename T>
Matrix<T>::Matrix(const Matrix&& other) noexcept
    : _dimension(other._dimension) {
  _mat = other._mat;
  std::cout << "Inside the move Constructor" << std::endl;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) noexcept {
  _dimension = other._dimension;
  _mat = other._mat;
  std::cout << "Inside the Equals Operator" << std::endl;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix&& other) noexcept {
  _dimension = other._dimension;
  _mat = other._mat;
  std::cout << "Inside the move equals Operator" << std::endl;
}

template <typename T>
std::pair<size_t, size_t>& Matrix<T>::GetDimension() const {
  return _dimension;
}

template <typename T>
void Matrix<T>::Print() const {
  if (_dimension.first == 0) {
    std::cout << "Empty Matrix";
  }
  for (size_t i = 0; i < _mat.size(); ++i) {
    for (size_t j = 0; j < _mat[0].size(); ++j) {
      std::cout << _mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
void Matrix<T>::IndexAssign(size_t row, size_t col, T val) {
  try {
    _mat.at(row).at(col) = val;
  } catch (...) {
    std::cout << "index out of bounds"
              << "\n";
  }
}

template <typename T>
Matrix<T> Matrix<T>::Transpose() const {
  T init_val{};
  Matrix new_mat(this->_dimension.second, this->_dimension.first, init_val);
  for (int i = 0; i < new_mat._mat.size(); ++i) {
    for (int j = 0; j < new_mat._mat[0].size(); ++j) {
      new_mat._mat[i][j] = _mat[j][i];
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const {
  if (this->_dimension.second != rhs._dimension.first) {
    std::cout
        << "Incorrect matrix multiplication dimensions. Returning Empty Matrix"
        << std::endl;
    Matrix mat1;
    return mat1;
  }
  T init_val{};
  Matrix new_mat(this->_dimension.first, rhs._dimension.second, init_val);
  T sum;
  for (int i = 0; i < new_mat._mat.size(); ++i) {
    for (int j = 0; j < new_mat._mat[0].size(); ++j) {
      sum = 0;
      for (int row_rhs = 0; row_rhs < rhs._mat.size(); ++row_rhs) {
        sum += this->_mat.at(i).at(row_rhs) * rhs._mat.at(row_rhs).at(j);
      }
      new_mat._mat[i][j] = sum;
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) const {
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = scalar * new_mat._mat[i][j];
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T scalar) const {
  if (scalar == 0) {
    std::cout << "Divinging by Zero is not possible. Returning Same Matrix"
              << std::endl;
    return *this;
  }
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = new_mat._mat[i][j] / scalar;
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const {
  if (this->_dimension.first != rhs._dimension.first &&
      this->_dimension.second != rhs._dimension.second) {
    std::cout << "Matrix Dimension mismatch. Returning empty matrix"
              << std::endl;
    Matrix empty_mat;
    return empty_mat;
  }
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = _mat[i][j] + rhs._mat[i][j];
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T scalar) const {
  if (this->_dimension.first == 0 && this->_dimension.second == 0) {
    std::cout << "Empty Matrix" << std::endl;
    Matrix empty_mat;
    return empty_mat;
  }
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = _mat[i][j] + scalar;
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) const {
  if (this->_dimension.first != rhs._dimension.first &&
      this->_dimension.second != rhs._dimension.second) {
    std::cout << "Matrix Dimension mismatch. Returning empty matrix"
              << std::endl;
    Matrix empty_mat;
    return empty_mat;
  }
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = _mat[i][j] - rhs._mat[i][j];
    }
  }
  return new_mat;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T scalar) const {
  if (this->_dimension.first == 0 && this->_dimension.second == 0) {
    std::cout << "Empty Matrix" << std::endl;
    Matrix empty_mat;
    return empty_mat;
  }
  Matrix new_mat(*this);
  for (int i = 0; i < _mat.size(); ++i) {
    for (int j = 0; j < _mat[0].size(); ++j) {
      new_mat._mat[i][j] = _mat[i][j] - scalar;
    }
  }
  return new_mat;
}

// Mainitaining Associative Properties
template <typename T>
Matrix<T> operator*(const T scalar, const Matrix<T>& rhs) {
  return rhs * scalar;
}

template <typename T>
Matrix<T> operator+(const T scalar, const Matrix<T>& rhs) {
  return rhs + scalar;
}

template <typename T>
Matrix<T> operator-(const T scalar, const Matrix<T>& rhs) {
  return rhs * (-1) + scalar;
}

int main() {
  // Checking Empty Matrix Initialization
  std::cout << "Checking Empty Matrix Initialization " << std::endl;
  std::cout << std::endl;
  Matrix<int> mat1;
  Matrix<double> mat2;
  Matrix<double> mat3;
  mat1.Print();
  mat2.Print();
  mat3.Print();
  // Checking Empty Matrix Operators
  mat2 = mat2 + mat3;
  mat2 = mat2 - mat3;
  mat2 = mat2 - 4;
  mat2.Print();

  // Initializing Matrix with fixed Initial Values
  std::cout << "Initializing Matrix with fixed Initial Values " << std::endl;
  std::cout << std::endl;
  Matrix<int> mat4(5, 2, 5);
  mat4.Print();

  // Initializing Matrix with vector
  std::cout << "Initializing Matrix with vector" << std::endl;
  Matrix<int> mat5(2, 5, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  mat5.Print();
  // Showing Incorrect Vector input handling
  std::cout << "Showing Incorrect Vector input handling" << std::endl;
  Matrix<int> mat6(2, 5, {1, 2});
  mat6.Print();

  // Showing Arithmetic Operations
  std::cout << "Showing Arithmetic Operations" << std::endl;
  mat6 = 2 + mat6 + 4;
  mat6.Print();

  mat6 = 1 - mat6 - 3 + 10;
  mat6.Print();

  mat6 = 3 * mat6 * 1;
  mat6.Print();

  std::cout << "Division as of now can only happen with scalar as RHS"
            << std::endl;
  mat6 = mat6 / 3;
  mat6.Print();

  // Showing Index Assign Operations
  std::cout << "Showing Index Assign Operations" << std::endl;
  std::cout << std::endl;
  mat6.IndexAssign(1, 1, 4);
  mat6.IndexAssign(1, 0, 9);
  mat6.IndexAssign(0, 4, -4);
  mat6.Print();
  std::cout << "Showing Index Assign Out of Bounds Handling" << std::endl;
  mat6.IndexAssign(0, 10, -4);
  mat6.Print();

  // Showing Matrix Transpose
  std::cout << "Showing Matrix Transpose" << std::endl;
  std::cout << std::endl;
  mat6 = mat6.Transpose();
  mat6.Print();

  // Matrix Multiplication
  std::cout << "Showing Matrix Multiplication" << std::endl;
  std::cout << std::endl;
  std::cout << "Multiplying the below Matrices" << std::endl;
  mat4.Print();
  mat5.Print();
  std::cout << "This gives" << std::endl;
  auto mat7 = mat4 * mat5;
  mat7.Print();
  std::cout << "Showing Incorrect Multiplication Handling" << std::endl;
  mat4.Print();
  mat7.Print();
  std::cout << "This gives" << std::endl;
  auto mat8 = mat4 * mat7;
  mat8.Print();

  // Matrix - Matrix Addition and Subtraction
  std::cout << "Showing Matrix- Matrix Addition and Subtraction" << std::endl;
  std::cout << std::endl;
  Matrix<int> mat9(2, 2, {1, 2, 3, 4});
  Matrix<int> mat10(2, 2, {5, 6, 7, 8});
  mat9.Print();
  mat10.Print();
  std::cout << "Addition"
            << "\n";
  auto mat11 = mat9 + mat10;
  mat11.Print();
  std::cout << "Subtraction"
            << "\n";
  mat11 = mat9 - mat10;
  mat11.Print();

  // Matrix - Matrix Division need to add.

  return 0;
}
