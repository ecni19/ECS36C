#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono> // NOLINT (build/c++11)

class Cities {
 public:
  Cities(int i, int c, int r) : inhab_(i), case_(c), recov_(r) {}

  /* < overload for the std::sort */
  bool operator<(Cities &rhs) {
    if (SafetyIndices() == rhs.SafetyIndices())
      return (inhab_ < rhs.inhab_);

    else
      return (SafetyIndices() < rhs.SafetyIndices());
  }

  /*calculating the safety index of cities */
  int SafetyIndices() {
    return safety_ = 10000.0 * ( 2.0 *
    (1 - (static_cast<double>(case_) / static_cast<double>(inhab_)))
    + (0.5) * (static_cast<double>(recov_) / static_cast<double>(case_)));
  }

 private:
  int inhab_;
  int case_;
  int recov_;
  int safety_;
};

/* class Time for counting elapsed microseconds for searches */
class Time {
 public:
  Time() {}

  void Reset() {
    start_ = std::chrono::high_resolution_clock::now();
  }

  double CurrentTime() {
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>
                        (end - start_).count();
    return elapsed_us;
  }

 private:
  std::chrono::high_resolution_clock::time_point start_;
};

/* generic function that opens files based on command line arguments */
std::fstream OpenFile(std::string file_name) {
  std::fstream file;
  file.open(file_name);

  if (!file.is_open()) {
    std::cerr << "Error: cannot open file " << file_name << std::endl;
    exit(1);
  } else {
    return file;
  }
}

/* generic function for creating a result file */
std::fstream CreateFile(std::string file_name) {
  std::fstream file;
  file.open(file_name, std::ios::out);

  if (!file.is_open()) {
    std::cerr << "Error: cannot open file " << file_name << std::endl;
    exit(1);
  } else {
    return file;
  }
}

/* executes a linear search */
int LinearSearch(std::vector<Cities> &city, std::vector<int> &safety) {
  int count = 0;

  for (unsigned int i = 0; i < safety.size(); i++) {
    for (unsigned int j = 0; j < city.size(); j++) {
      if (safety[i] == city[j].SafetyIndices()) {
        count += 1;

        break;
      }
    }
  }
  return count;
}

/* carries out a binary sesarch on the cities vector */
int BinarySearch(std::vector<Cities> &city, std::vector<int> &safety) {
  int low = 0;
  int high = city.size() - 1;

  int count = 0;

  for (unsigned int i = 0; i < safety.size(); i++) {
    low = 0;
    high = city.size() - 1;

    while (low <= high) {
      int mid = low + (high - low) / 2;

        if (city[mid].SafetyIndices() == safety[i]) {
          count += 1;

          break;
        }
        if (city[mid].SafetyIndices() < safety[i])
          low = mid + 1;
        else
          high = mid - 1;
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  std::vector<Cities>cities;
  std::vector<int>indices;

  Time ct;

  int index;
  int pop, cases, recov;

  char choice;
  bool quit = false;

  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
      << " <city_file.dat> <safety_file.dat> <result_file.dat>" << std::endl;
    exit(1);
  }

  std::fstream city_file = OpenFile(argv[1]);
  std::fstream index_file = OpenFile(argv[2]);
  std::fstream res_file = CreateFile(argv[3]);

  /* read in safety index and city files */
  while (index_file >> index)
    indices.push_back(index);

  while (city_file >> pop >> cases >> recov) {
    Cities c = Cities(pop, cases, recov);
    cities.push_back(c);
  }

  std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
  while (!quit) {
    std::cin >> choice;
    ct.Reset();

    switch (choice) {
      case 'l':
      {
        int count = LinearSearch(cities, indices);

        res_file << count << '\n';

        quit = true;

        break;
      }
      case 'b':
      {
        std::sort(cities.begin(), cities.end());

        int count = BinarySearch(cities, indices);

        res_file << count << '\n';

        quit = true;

        break;
      }
      default:
      {
        std::cerr << "Incorrect choice" << std::endl;
        quit = false;
      }
    }
  }

  std::cout << "CPU time: " << ct.CurrentTime()
          << " microseconds" << std::endl;

  city_file.close();
  index_file.close();
  res_file.close();

  return 0;
}
