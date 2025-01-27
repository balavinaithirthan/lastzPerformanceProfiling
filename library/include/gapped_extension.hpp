
#pragma once
#include "hit.hpp"
#include "two_matrix.hpp"
#include <vector>

namespace perf {
std::vector<Hit> gappedExtension(std::vector<Hit> hits,
                                 const std::string &query,
                                 const std::string &reference);
Matrix gappedExtensionFilter(Hit &hit, const std::string &query,
                             const std::string &reference);

void findAnchorFilter(Hit &hit, Matrix dp);

} // namespace perf