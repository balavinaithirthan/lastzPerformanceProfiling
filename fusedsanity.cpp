void nonFusedExample(const std::vector<int> &b, const std::vector<int> &c,
                     std::vector<int> &a) {
  size_t size = b.size();
  std::vector<int> temp(size);

  // First loop: calculate temp = b + c
  for (size_t i = 0; i < size; ++i) {
    temp[i] = b[i] + c[i];
  }

  // Second loop: assign temp to a
  for (size_t i = 0; i < size; ++i) {
    a[i] = temp[i];
  }
}

void fusedExample(const std::vector<int> &b, const std::vector<int> &c,
                  std::vector<int> &a) {
  size_t size = b.size();

  // Single loop: directly calculate a = b + c
  for (size_t i = 0; i < size; ++i) {
    a[i] = b[i] + c[i];
  }
}

int fusionExampleMain() {
  size_t n = 100000000; // Number of elements
  std::vector<int> b(n), c(n), a(n);

  // Fill b and c with random data
  std::random_device rd;                       // Seed generator
  std::mt19937 gen(rd());                      // Random number generator
  std::uniform_int_distribution<> dis(1, 100); // Uniform distribution [1, 100]

  for (size_t i = 0; i < n; ++i) {
    b[i] = dis(gen);
    c[i] = dis(gen);
  }

  // Non-fused execution
  auto start = std::chrono::high_resolution_clock::now();
  nonFusedExample(b, c, a);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Non-Fused Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms\n";

  // Fused execution
  start = std::chrono::high_resolution_clock::now();
  fusedExample(b, c, a);
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Fused Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << " ms\n";
  printf("a end = %d\n", a[n - 1]);

  return 0;
}
