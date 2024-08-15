struct MatrixTerm {
  int row;
  int col;
  float value;
};

class SparseMatrix {
 public:
  SparseMatrix(int num_rows_, int num_cols_, int capacity_);

  SparseMatrix(const SparseMatrix& b);

  ~SparseMatrix();

  void SetValue(int row, int col, int value);

  float Getvalue(int row, int col) const;

  SparseMatrix Transpose() const;

  void PrintTerms() const;
  void Print() const;

 private:
  MatrixTerm* terms_ = nullptr;
  int num_rows_ = 0;
  int num_cols_ = 0;
  int num_terms_ = 0;
  int capacity_ = 0;
};