#include <vector>

class Matrix {
 public:
  Matrix(int num_rows, int num_cols);
  Matrix(const Matrix& b);
  ~Matrix() = default;

  void SetValue(int row, int col, int value);

  float GetValue(int row, int col) const;

  Matrix Add(const Matrix& b);

  Matrix Transpose();

  void Print();

 private:
  std::vector<std::vector<float>> values_;
  int num_rows_ = 0;
  int num_cols_ = 0;
};