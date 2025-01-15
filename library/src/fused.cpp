#include "1d_exact_filter.hpp"
#include "needleman.hpp"
namespace perf {
void fuse(std::vector<Hit> &hits, const std::string &query,
          const std::string &reference) {
  for (auto &hit : hits) {
    if (!hit.on) {
      oneDimExactFilter(hit, query, reference);
    } else {
      needlemanWunschFilter(hit, query, reference);
    }
  }
}

} // namespace perf