#include "chaining.hpp"
#include "fused.hpp"
#include "needleman.hpp"
#include <1d_exact_filter.hpp>
#include <chrono>
#include <cstddef>
#include <findHits.hpp>
#include <helloworld.hpp>
#include <iostream>
#include <remove_overlap.hpp>
#include <seed.hpp>

void debugHits(std::vector<perf::Hit> hits) {
  std::cout << "hits: ";
  for (double i = 0; i < hits.size(); i++) {
    if (hits[i].on)
      std::cout << "{ " << hits[i].getX() << " " << hits[i].getY() << " "
                << hits[i].length << " }";
  }
}

void debugMap(std::map<std::string, std::vector<size_t>> map) {
  for (const auto &entry : map) {
    std::cout << entry.first << " ";
    for (const auto &pos : entry.second) {
      std::cout << pos << " ";
    }
    std::cout << std::endl;
  }
}

void checkNumberOn(std::vector<perf::Hit> hits) {
  double count = 0;
  for (double i = 0; i < hits.size(); i++) {
    if (hits[i].on) {
      count += 1;
    }
  }
  std::cout << "count" << count << std::endl;
}

int main() {
  size_t size = 1000;
  const std::string QUERY = std::string(size, 'A');
  const std::string REFERENCE = std::string(size, 'A');
  double n = 4;
  auto map_one = perf::findSeeds(QUERY, n);
  auto map_two = perf::findSeeds(REFERENCE, n);
  auto hits = perf::findHits(map_one, map_two, n);

  /// filters
  auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
  auto no_overlap = perf::remove_overlap(filtered_hits);
  auto chains = perf::chaining(no_overlap);
  auto results = perf::needlemanWunsch(chains, QUERY, REFERENCE);

  return 0;
  ////

  // auto total_start = std::chrono::high_resolution_clock::now();
  // Measure time for fused
  // auto start = std::chrono::high_resolution_clock::now();

  // perf::fuse(hits, QUERY, REFERENCE);

  // auto end = std::chrono::high_resolution_clock::now();

  // std::cout << "fused took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // Measure time for oneDimExact
  // auto start = std::chrono::high_resolution_clock::now();
  // auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
  // auto end = std::chrono::high_resolution_clock::now();
  // std::cout << "oneDimExact took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // start = std::chrono::high_resolution_clock::now();
  // filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
  // end = std::chrono::high_resolution_clock::now();
  // std::cout << "oneDimExact 2 took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // // Measure time for remove_overlap
  // start = std::chrono::high_resolution_clock::now();
  // auto no_overlap = perf::remove_overlap(filtered_hits);
  // end = std::chrono::high_resolution_clock::now();
  // std::cout << "remove_overlap took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // // Measure time for chaining
  // start = std::chrono::high_resolution_clock::now();
  // auto chains = perf::chaining(no_overlap);
  // end = std::chrono::high_resolution_clock::now();
  // std::cout << "chaining took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // // Measure time for needlemanWunsch
  // start = std::chrono::high_resolution_clock::now();
  // auto results = perf::needlemanWunsch(no_overlap, QUERY, REFERENCE);
  // end = std::chrono::high_resolution_clock::now();
  // std::cout << "needlemanWunsch took: "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    start)
  //                  .count()
  //           << " ms" << std::endl;

  // // // Total time
  // // auto total_end = std::chrono::high_resolution_clock::now();
  // // std::cout << "Total time: "
  // //           << std::chrono::duration_cast<std::chrono::milliseconds>(
  // //                  total_end - total_start)
  // //                  .count()
  //           << " ms" << std::endl;
  // // generate set of hits -nmer flag
  // // one extension --xdrop flag, --hsp threshold
  // // -- recoverseeds so you don't need to do diagonal hashing
  // // chaining
  // // gapped extension
}