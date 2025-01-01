#include "findHits.hpp"
#include <cstddef>
#include <string>

namespace perf {

std::vector<Hit> findHits(std::map<std::string, std::vector<size_t>> a,
                          std::map<std::string, std::vector<size_t>> b, int n) {
  std::vector<Hit> hits;
  for (const auto &entry : a) {
    const std::string &seed = entry.first;
    if (b.find(seed) != b.end()) {
      const std::vector<size_t> positions_a = std::move(entry.second);
      const std::vector<size_t> positions_b = std::move(b.at(seed));
      for (const auto &pos_1 : positions_a) {
        for (const auto &pos_2 : positions_b) {
          auto position = std::tuple<size_t, size_t>{
              pos_1, pos_2}; // auto move bc temp value
          hits.push_back(std::move(Hit(position, n)));
        }
      }
    }
  }
  return hits;
}
} // namespace perf