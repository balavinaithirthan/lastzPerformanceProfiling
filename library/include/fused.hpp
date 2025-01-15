#include "hit.hpp"
#include <vector>

namespace perf {
void fuse(std::vector<Hit> &hits, const std::string &query,
          const std::string &reference);
}