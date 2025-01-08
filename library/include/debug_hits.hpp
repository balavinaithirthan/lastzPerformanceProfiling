#include "hit.hpp"
#include <iostream>

namespace perf {
inline void debug_hits(std::vector<Hit> hits) {
  for (double i = 0; i < hits.size(); i++) {
    std::cout << hits[i].getX() << " " << hits[i].getY() << " "
              << hits[i].length;
  }
}
} // namespace perf