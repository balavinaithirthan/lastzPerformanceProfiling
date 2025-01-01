#include "hit.hpp"
#include <map>
#include <vector>

namespace perf {
std::vector<Hit> findHits(std::map<std::string, std::vector<size_t>> a,
                          std::map<std::string, std::vector<size_t>> b, int c);
} // namespace perf