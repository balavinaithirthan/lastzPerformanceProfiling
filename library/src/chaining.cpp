#include "chaining.hpp"
#include "debug_hits.hpp"
#include "hit.hpp"
#include <cstddef>
#include <iostream>
#include <numeric>
// notes: w is just length
// need to sort hits before

namespace perf {
double gap(const Hit &target, const Hit &prevHit) {
  return abs((target.getY() - prevHit.getY()) -
             (target.getX() - prevHit.getX()));
}

double match(const Hit &target, const Hit &prevHit) {
  return std::min(target.getY() - prevHit.getY(),
                  std::min(target.getX() - prevHit.getX(), target.length));
}

std::vector<Hit> backtracking(std::vector<Hit> &hits, std::vector<double> &dp,
                              std::vector<double> pred) {
  std::vector<bool> used(hits.size(), false);
  std::vector<Hit> newHits{};
  for (double i = dp.size() - 1; i >= 0; i--) {
    double j = i;
    std::vector<Hit> chain{};
    while (pred[j] != -1 and used[j] != true) {
      chain.push_back(hits[j]);
      j = pred[j];
      used[j] = true;
    }
    double length = 0;
    for (const auto &chainHit : chain) {
      length += chainHit.length;
    }
    if (chain.size() > 0) {
      newHits.push_back(
          Hit(std::tuple<size_t, size_t>(chain[0].getX(), chain[0].getY()),
              length));
    }
  }
  return newHits;
}

void debug(std::vector<double> dp, std::vector<double> pred) {
  for (double i = 0; i < dp.size(); i++) {
    std::cout << dp[i] << " ";
  }
}

// hits should have been sorted
std::vector<Hit> chaining(std::vector<Hit> hits) {
  std::vector<double> dp(hits.size(), 0); // Initialize dp vector with zeros
  std::vector<double> pred(hits.size(), 0);
  for (double i = 0; i < hits.size(); i++) {
    dp[i] = hits[i].length; // inital score
    pred[i] = -1;
    for (double j = i; j >= 0; j--) {
      auto gap_cost = gap(hits[i], hits[j]);
      auto match_score = match(hits[i], hits[j]);
      auto score = dp[j] + gap_cost + match_score;
      if (score > dp[i]) {
        dp[i] = score;
        pred[i] = j;
      }
    }
  }
  auto newHits = backtracking(hits, dp, pred);
  return hits;
}

} // namespace perf