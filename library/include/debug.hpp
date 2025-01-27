#include "hit.hpp"
#include "two_matrix.hpp"
#include <iostream>
#include <map>
namespace perf {
inline void debugHits(std::vector<perf::Hit> hits) {
  std::cout << "hits: ";
  for (double i = 0; i < hits.size(); i++) {
    if (hits[i].on)
      std::cout << "{ " << hits[i].getX() << " " << hits[i].getY() << " "
                << hits[i].length << " }";
  }
}

inline void debugMap(std::map<std::string, std::vector<size_t>> map) {
  for (const auto &entry : map) {
    std::cout << entry.first << " ";
    for (const auto &pos : entry.second) {
      std::cout << pos << " ";
    }
    std::cout << std::endl;
  }
}

inline void debugMatrix(Matrix matrix) {
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      std::cout << matrix.get(i, j) << " ";
    }
    std::cout << std::endl;
  }
}
} // namespace perf