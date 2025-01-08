#ifndef SEED_HPP
#define SEED_HPP

#include <iostream>
#include <map>
#include <string>

namespace perf {
std::map<std::string, std::vector<size_t>> findSeeds(const std::string &input,
                                                     double n);
} // namespace perf

#endif // SEED_HPP