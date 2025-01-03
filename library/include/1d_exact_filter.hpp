#include "hit.hpp"

namespace perf {

std::vector<Hit> oneDimExact(std::vector<Hit> hits, const std::string &query,
                             const std::string &reference);

void oneDimExactFilter(Hit &hit, const std::string &query,
                       const std::string &reference);

} // namespace perf