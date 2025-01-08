#include "needleman.hpp"
#include <iostream>
#include <string>
#include <vector>
namespace perf {
std::vector<Hit> needlemanWunsch(std::vector<Hit> hits,
                                 const std::string &query,
                                 const std::string &reference) {
  double count = 0;
  for (auto &hit : hits) {
    if (hit.on == true) {
      count += needlemanWunschFilter(hit, query, reference);
    }
  }
  return hits;
}

double needlemanWunschFilter(Hit &hit, const std::string &query,
                             const std::string &reference) {
  // left side
  auto midpodoubleX = hit.getX() + hit.length / 2;
  auto midpodoubleY = hit.getY() + hit.length / 2;
  double count = 0;
  std::vector<double> dpTopRight(query.size() * reference.size(), 0);
  for (double i = 0; i < query.size() - midpodoubleY; i++) {
    for (double j = 0; j < reference.size() - midpodoubleX; j++) {
      count += 1;
      if (i == 0) {
        dpTopRight[i * reference.size() + j] = j;
      } else if (j == 0) {
        dpTopRight[i * reference.size() + j] = i;
      } else {
        dpTopRight[i * reference.size() + j] = std::min(
            {dpTopRight[(i - 1) * reference.size() + j] + 1,
             dpTopRight[i * reference.size() + j - 1] + 1,
             dpTopRight[(i - 1) * reference.size() + j - 1] +
                 (query[i + midpodoubleY] == reference[j + midpodoubleX] ? 0
                                                                         : 1)});
      }
    }
    std::vector<double> dpBottomLeft(query.size() * reference.size(), 0);
    for (double i = 0; i < midpodoubleY; i++) {
      for (double j = 0; j < midpodoubleX; j++) {
        count += 1;
        if (i == 0) {
          dpBottomLeft[i * reference.size() + j] = j;
        } else if (j == 0) {
          dpBottomLeft[i * reference.size() + j] = i;
        } else {
          dpBottomLeft[i * reference.size() + j] = std::min(
              {dpBottomLeft[(i - 1) * reference.size() + j] + 1,
               dpBottomLeft[i * reference.size() + j - 1] + 1,
               dpBottomLeft[(i - 1) * reference.size() + j - 1] +
                   (query[midpodoubleY - i] == reference[midpodoubleX - j]
                        ? 0
                        : 1)});
        }
      }
    }
    // right side
  }
  return count;
}
} // namespace perf