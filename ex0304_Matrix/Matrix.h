class Matrix {
 public:
  Matrix(int num_rows, int num_cols);
  Matrix(const Matrix& b);
  ~Matrix();

  void SetValue(int row, int col, int value);

  float GetValue(int row, int col) const;

  Matrix Add(const Matrix& b);

  Matrix Transpose();

  void Print();

 private:
  //   float** values_ = nullptr; //2차원
  float* values_ = nullptr;  // 1차원
  int num_rows_ = 0;
  int num_cols_ = 0;
};