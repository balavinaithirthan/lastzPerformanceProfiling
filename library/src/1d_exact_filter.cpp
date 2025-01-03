#include "1d_exact_filter.hpp"
#include <string>
#include <vector>

// Todo, masking
namespace perf {

std::vector<Hit> oneDimExact(std::vector<Hit> hits, const std::string &query,
                             const std::string &reference) {
  for (auto &hit : hits) {
    if (hit.on == true) {
      oneDimExactFilter(hit, query, reference);
    }
  }
  return hits;
}

void oneDimExactFilter(Hit &hit, const std::string &query,
                       const std::string &reference) {
  auto x1 = hit.getX();
  auto y1 = hit.getY();
  auto x2 = hit.getX() + hit.length;
  auto y2 = hit.getY() + hit.length;

  // right side
  auto i = y2;
  auto j = x2;
  while (query.at(i) == reference.at(j)) {
    hit.length += 1;
    i += 1;
    j += 1;
  }

  i = y1;
  j = x1;
  // left side
  while (query.at(i) == reference.at(j)) {
    hit.length += 1;
    i -= 1;
    j -= 1;
    std::get<0>(hit.position) -= 1;
    std::get<1>(hit.position) -= 1;
  }
}
} // namespace perf