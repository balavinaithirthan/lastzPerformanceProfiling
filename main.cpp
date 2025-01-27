#include <library.hpp>

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

void turnCertainHitsOn(std::vector<perf::Hit> &hits, size_t vecSize) {
  for (double i = 0; i < hits.size(); i++) {
    hits[i].on = false;
  }

  for (double i = 0; i < vecSize; i++) {
    double num = std::rand() % hits.size();
    hits[num].on = true;
  }
}

void timeFused(std::vector<perf::Hit> hits, const std::string &query,
               const std::string &reference) {
  auto start = std::chrono::high_resolution_clock::now();
  // basic fuse example
  turnCertainHitsOn(hits, 10);
  perf::fuse(hits, query, reference);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "fused took: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms" << std::endl;
}

void timeIndepFilters(std::vector<perf::Hit> hits, const std::string &query,
                      const std::string &reference) {
  auto start = std::chrono::high_resolution_clock::now();
  // oneDimExact
  auto filtered_hits = perf::oneDimExact(hits, query, reference);
  // needlemanWunsch
  turnCertainHitsOn(hits, 10);
  auto results = perf::needlemanWunsch(filtered_hits, query, reference);
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << "result time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms" << std::endl;
}

// int main() {
//   Not
//   size_t size = 50;
//   const std::string QUERY = std::string(size, 'A');
//   const std::string REFERENCE = std::string(size, 'A');
//   double n = 4;
//   auto map_one = perf::findSeeds(QUERY, n);
//   auto map_two = perf::findSeeds(REFERENCE, n);
//   auto hits = perf::findHits(map_one, map_two, n);
//   timeFused(hits, QUERY, REFERENCE);
//   timeIndepFilters(hits, QUERY, REFERENCE);
//   return 0;
// filters
// auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
// auto no_overlap = perf::remove_overlap(filtered_hits);
// auto chains = perf::chaining(no_overlap);
// auto results = perf::needlemanWunsch(chains, QUERY, REFERENCE);

// return 0;
////

// Measure time for oneDimExact
// auto start = std::chrono::high_resolution_clock::now();
// auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
// auto end = std::chrono::high_resolution_clock::now();
// std::cout << "oneDimExact took: "
//           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
// start)
//                  .count()
//           << " ms" << std::endl;

// start = std::chrono::high_resolution_clock::now();
// auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
// end = std::chrono::high_resolution_clock::now();
// std::cout << "oneDimExact 2 took: "
//           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
// start)
//                  .count()
//           << " ms" << std::endl;

// // Measure time for remove_overlap
// start = std::chrono::high_resolution_clock::now();
// auto no_overlap = perf::remove_overlap(filtered_hits);
// end = std::chrono::high_resolution_clock::now();
// std::cout << "remove_overlap took: "
//           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
// start)
//                  .count()
//           << " ms" << std::endl;

// // Measure time for chaining
// start = std::chrono::high_resolution_clock::now();
// auto chains = perf::chaining(no_overlap);
// end = std::chrono::high_resolution_clock::now();
// std::cout << "chaining took: "
//           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
// start)
//                  .count()
//           << " ms" << std::endl;

// // Measure time for needlemanWunsch
// start = std::chrono::high_resolution_clock::now();
// auto results = perf::needlemanWunsch(filtered_hits, QUERY, REFERENCE);
// end = std::chrono::high_resolution_clock::now();
// std::cout << "needlemanWunsch took: "
//           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
// start)
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
//   // // gapped extension
// }
