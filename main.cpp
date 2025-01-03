#include <1d_exact_filter.hpp>
#include <findHits.hpp>
#include <helloworld.hpp>
#include <iostream>
#include <remove_overlap.hpp>
#include <seed.hpp>

int main() {
  const std::string QUERY = "ABJIEFOPWEPQ";
  const std::string REFERENCE = "JDIEOWJDFIOQWQ";
  int n = 4;
  auto map_one = perf::findSeeds(QUERY, n);
  auto map_two = perf::findSeeds(REFERENCE, n);
  auto hits = perf::findHits(map_one, map_two, n);
  auto filtered_hits = perf::oneDimExact(hits, QUERY, REFERENCE);
  auto no_overlap = perf::remove_overlap(filtered_hits);

  // generate set of hits -nmer flag
  // one extension --xdrop flag, --hsp threshold
  // -- recoverseeds so you don't need to do diagonal hashing
  // chaining
  // gapped extension
}