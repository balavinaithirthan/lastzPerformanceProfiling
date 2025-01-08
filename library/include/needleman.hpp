#include "hit.hpp"
#include <vector>

namespace perf {

std::vector<Hit> needlemanWunsch(std::vector<Hit> hits,
                                 const std::string &query,
                                 const std::string &reference);

double needlemanWunschFilter(Hit &hit, const std::string &query,
                             const std::string &reference);
} // namespace perf