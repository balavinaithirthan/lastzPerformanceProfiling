#include "gapped_extension.hpp"
#include "hit.hpp"
#include "two_matrix.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace perf {

// example of fusion: find max inside the actual gapped Extension filter
void findAnchorFilter(Hit &hit, Matrix dp) {
  double max = 0;
  size_t x = 0;
  size_t y = 0;
  for (size_t i = 0; i < dp.getRows(); i++) {
    for (size_t j = 0; j < dp.getCols(); j++) {
      if (dp.get(i, j) > max) {
        max = dp.get(i, j);
        x = i;
        y = j;
      }
    }
  }
  hit.setPosition(x, y);
  hit.length = 1;
}

Matrix gappedExtensionFilter(Hit &hit, const std::string &query,
                             const std::string &reference) {
  const int GAP = -2;
  const int MATCH = 1;
  const int MISMATCH = -1;
  const int REGION_WIDTH =
      hit.length; // we don't count the root(2) from earlier
  const int REGION_HEIGHT = hit.length;
  auto needlemanDP = Matrix(REGION_HEIGHT, REGION_WIDTH);
  for (size_t i = 0; i < REGION_HEIGHT; i++) {
    needlemanDP.set(i, 0, i * GAP);
  }
  for (size_t j = 0; j < REGION_WIDTH; j++) {
    needlemanDP.set(0, j, j * GAP);
  }
  for (size_t i = 1; i < REGION_HEIGHT; i++) {
    for (size_t j = 1; j < REGION_WIDTH; j++) {
      int match = needlemanDP.get(i - 1, j - 1) +
                  (query.at(i) == reference.at(j) ? MATCH : MISMATCH);
      int delete_ = needlemanDP.get(i - 1, j) + GAP;
      int insert = needlemanDP.get(i, j - 1) + GAP;
      needlemanDP.set(i, j, std::max(match, std::max(delete_, insert)));
    }
  }
  return needlemanDP;
}

std::vector<Hit> gappedExtension(std::vector<Hit> hits,
                                 const std::string &query,
                                 const std::string &reference) {
  for (auto &hit : hits) {
    if (hit.on) {
      auto dp = gappedExtensionFilter(hit, query, reference);
      findAnchorFilter(hit, std::move(dp));
    }
  }
  return hits;
}

} // namespace perf