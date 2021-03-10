#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0]
        << " <num_cities> <num_safeties> <suffix> [seed]"
        << std::endl;
    exit(1);
  }

  int ncities = std::stoi(argv[1]);
  int nsafeties = std::stoi(argv[2]);
  if (ncities <= 0 || nsafeties <= 0) {
    std::cerr << "Error: wrong arguments" << std::endl;
    exit(1);
  }

  std::ofstream cities, safeties;
  cities.open(std::string("cities_") + argv[3] + ".dat",
             std::ofstream::trunc);
  safeties.open(std::string("safety_") + argv[3] + ".dat",
            std::ofstream::trunc);
  if (!cities.good() || !safeties.good()) {
    std::cerr << "Error: cannot open output file(s)" << std::endl;
    exit(1);
  }

  /* random generator */
  std::random_device rd;
  std::mt19937 mt(rd());

  if (argc == 5) {
    int seed = std::stoi(argv[4]);
    if (seed < 0) {
      std::cerr << "Error: wrong seed" << std::endl;
      exit(1);
    }
    mt.seed(seed);
  }

  /* random number distribution for cities */
  std::uniform_int_distribution<int> city_dist(0, ncities);
  for (int i = 0; i < ncities; i++) {
    int recovs = city_dist(mt);
    int cases = recovs + city_dist(mt);
    int inhabs = cases + city_dist(mt);
    cities << inhabs << " " << cases << " " << recovs << "\n";
  }

  /* random number distribution for safeties */
  std::uniform_int_distribution<int> safety_dist(0, 25000);
  for (int i = 0; i < nsafeties; i++)
    safeties << safety_dist(mt) << "\n";

  cities.close();
  safeties.close();

  return 0;
}
