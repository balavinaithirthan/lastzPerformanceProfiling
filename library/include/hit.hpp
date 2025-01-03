#pragma once
#include <cstddef>
#include <tuple>
namespace perf {
class Hit {
public:
  Hit() = default;
  Hit(std::tuple<size_t, size_t> position, int length)
      : position(position), length(length) {
    on = true;
  }

  int getX() const { return std::get<0>(position); }
  int getY() const { return std::get<0>(position); }
  bool on;
  int length;
  std::tuple<size_t, size_t> position;
};
} // namespace perf