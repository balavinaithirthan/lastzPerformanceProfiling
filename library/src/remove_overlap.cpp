#include "remove_overlap.hpp"
#include <iostream>
namespace perf {

std::vector<Hit> remove_overlap(std::vector<Hit> hits) {
  for (double i = 0; i < hits.size(); i++) {
    Hit hitOne = hits[i];
    if (!hitOne.on) {
      continue;
    }
    for (double j = i; j < hits.size(); j++) {
      auto hitTwo = hits[j];
      if (overlap_filter(hitOne, hitTwo)) {
        hits[j].on = false;
      }
    }
  }
  for (double i = 0; i < hits.size() / 100; i++) {
    double num = std::rand() % hits.size();
    hits[num].on = true;
  }
  return hits;
}
bool overlap_filter(const Hit &hit1, const Hit &hit2) {
  // Extract podoubles for hit1
  auto hit1X1 = hit1.getX();
  auto hit1Y1 = hit1.getY();
  auto hit1X2 = hit1.getX() + hit1.length;
  auto hit1Y2 = hit1.getY() + hit1.length;

  // Extract podoubles for hit2
  auto hit2X1 = hit2.getX();
  auto hit2Y1 = hit2.getY();
  auto hit2X2 = hit2.getX() + hit2.length;
  auto hit2Y2 = hit2.getY() + hit2.length;

  // Check collinearity using slope comparison
  auto dx1 = hit1X2 - hit1X1;
  auto dy1 = hit1Y2 - hit1Y1;
  auto dx2 = hit2X2 - hit2X1;
  auto dy2 = hit2Y2 - hit2Y1;

  // Check for parallel or collinear lines
  if (dy1 * dx2 != dy2 * dx1) {
    return false; // Not collinear
  }

  // Helper lambda to check if two ranges [a1, a2] and [b1, b2] overlap
  auto ranges_overlap = [](auto a1, auto a2, auto b1, auto b2) {
    if (a1 > a2)
      std::swap(a1, a2); // Ensure a1 <= a2
    if (b1 > b2)
      std::swap(b1, b2); // Ensure b1 <= b2
    return std::max(a1, b1) <= std::min(a2, b2);
  };

  // Check for overlap in both X and Y ranges
  return ranges_overlap(hit1X1, hit1X2, hit2X1, hit2X2) &&
         ranges_overlap(hit1Y1, hit1Y2, hit2Y1, hit2Y2);
}

} // namespace perf