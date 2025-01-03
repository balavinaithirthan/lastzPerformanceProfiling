#include "hit.hpp"
#include <vector>

namespace perf {
std::vector<Hit> remove_overlap(std::vector<Hit> hits);
bool overlap_filter(const Hit &hitOne, const Hit &hitTwo);
} // namespace perf