#include <findHits.hpp>
#include <helloworld.hpp>
#include <iostream>
#include <seed.hpp>

int main() {
  std::string query = "ACGTACGTACGTACGT";
  std::string reference = "ATCGTACGT";
  int n = 4;
  auto map_one = perf::findSeeds(query, n);
  auto map_two = perf::findSeeds(reference, n);
  auto hits = perf::findHits(map_one, map_two, n);

  // generate set of hits -nmer flag
  // one extension --xdrop flag, --hsp threshold
  // -- recoverseeds so you don't need to do diagonal hashing
  // chaining
  // gapped extension
}