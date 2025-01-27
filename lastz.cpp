#include "library.hpp"
#include <chrono>
#include <iostream>

std::vector<perf::Hit> fusedKernel() {
  double kmer_size = 4;
  auto map_one = perf::findSeeds(perf::QUERY, kmer_size);
  auto map_two = perf::findSeeds(perf::REFERENCE, kmer_size);
  auto hits = perf::findHits(map_one, map_two, kmer_size);

  auto start = std::chrono::high_resolution_clock::now(); // Start timing
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (auto &hit : hits) {
    // if (hit.on) {
    perf::oneDimExactFilter(hit, perf::QUERY, perf::REFERENCE);
    //}
    // if (hit.on) {
    auto dp = perf::gappedExtensionFilter(hit, perf::QUERY, perf::REFERENCE);
    perf::findAnchorFilter(hit, dp);
    //}
    // if (hit.on) {
    perf::needlemanWunschFilter(hit, perf::QUERY, perf::REFERENCE);
    //}
  }

  auto end = std::chrono::high_resolution_clock::now(); // End timing
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time taken for fused: " << elapsed.count() << " seconds"
            << std::endl;

  return hits;
}

std::vector<perf::Hit> normalKernel() {
  double kmer_size = 4;
  auto map_one = perf::findSeeds(perf::QUERY, kmer_size);
  auto map_two = perf::findSeeds(perf::REFERENCE, kmer_size);
  auto hits = perf::findHits(map_one, map_two, kmer_size);

  auto start = std::chrono::high_resolution_clock::now(); // Start timing

  hits = perf::oneDimExact(std::move(hits), perf::QUERY, perf::REFERENCE);
  hits = gappedExtension(std::move(hits), perf::QUERY, perf::REFERENCE);
  hits = perf::needlemanWunsch(std::move(hits), perf::QUERY, perf::REFERENCE);

  auto end = std::chrono::high_resolution_clock::now(); // End timing
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time normal taken: " << elapsed.count() << " seconds"
            << std::endl;

  return hits;
}

std::vector<bool> generate_random_mask(float prob) {
  std::vector<bool> mask{};
  for (int i = 0; i < 100; i++) {
    mask.push_back(rand() % 100 < prob);
  }
  return mask;
}

void vector_removal(std::vector<perf::Hit> &hits) {
  for (auto it = hits.begin(); it != hits.end();) {
    if (it->on == false) {
      it = hits.erase(it);
    } else {
      ++it;
    }
  }
}

void vector_turn_off(std::vector<perf::Hit> &hits) {
  std::vector<bool> mask = generate_random_mask(0.5); // randomize
  for (int i = 0; i < hits.size(); i++) {
    if (mask[i] == true) {
      hits[i].on = false;
    }
  }
}

int main() {
  double kmer_size = 4;
  volatile auto ans1 = fusedKernel();
  volatile auto ans2 = normalKernel();
  return 0;
}
