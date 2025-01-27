#pragma once
#include <iostream>
#include <vector>

namespace perf {
class Matrix {
public:
  Matrix(size_t rows, size_t cols)
      : height(rows), width(cols), data(rows * cols, 0.0) {}
  std::vector<double>::iterator begin() { return data.begin(); }
  std::vector<double>::const_iterator begin() const { return data.begin(); }
  std::vector<double>::iterator end() { return data.end(); }
  std::vector<double>::const_iterator end() const { return data.end(); }

  ~Matrix() {}

  double get(size_t row, size_t col) const { return data[row * width + col]; }

  void set(size_t row, size_t col, double value) {
    data[row * width + col] = value;
  }
  size_t getRows() const { return height; }

  size_t getCols() const { return width; }

  void print() {
    for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
        std::cout << data[i * width + j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  size_t width;
  size_t height;
  std::vector<double> data;
};

} // namespace perf

// example usage: