#include "1d_exact_filter.hpp"
#include "needleman.hpp"
namespace perf {
void fuse(std::vector<Hit> &hits, const std::string &query,
          const std::string &reference) {
  for (double i = 0; i < hits.size() / 100; i++) {
    double num = std::rand() % hits.size();
    hits[num].on = true;
  }

  for (auto &hit : hits) {
    if (!hit.on) {
      continue;
    }
    oneDimExactFilter(hit, query, reference);
    needlemanWunschFilter(hit, query, reference);
  }
}

} // namespace perf