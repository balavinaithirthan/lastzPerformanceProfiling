#include <cstddef>
#include <tuple>
namespace perf {
class Hit {
public:
  Hit() = default;
  Hit(std::tuple<size_t, size_t> position, int length)
      : position_(position), length_(length) {}

  int getX() const { return std::get<0>(position_); }
  int getY() const { return std::get<0>(position_); }
  int getLength() const { return length_; }

private:
  std::tuple<size_t, size_t> position_;
  int length_;
};
} // namespace perf