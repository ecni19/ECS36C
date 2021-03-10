#include "multiset.h"
#include <iostream>
#include <string>

void PrimeFactors (Multiset<int> &mset, unsigned int &n) {
  // will keep on dividing by 2 as long as n is even
  // finds how many 2s are in the number.
  while (n % 2 == 0) {
    mset.Insert(2);
    n = n / 2;
  }

  for (unsigned int i = 3; i <= n; i += 2) {
    while (n % i == 0) {
      mset.Insert(i);
      n = n / i;
    }
  }

}
void PrintFactors (Multiset<int> &mset, std::string operation, std::string near) {

  if (mset.Empty() || mset.Size() == 1) {
   std::cout << "No prime factors";
   return;
  } 

  if (operation == "all") {
    for (int i = mset.Min(); i < mset.Max();) {
      int cur_factor = mset.Ceil(i);
      if (mset.Contains(cur_factor)) {
        std::cout << cur_factor << " (x" << mset.Count(cur_factor) << "), ";
        i = cur_factor + 1;
      }
    }
  } else if (operation == "max") {
      int max = mset.Max();
      std::cout << max << " (x" << mset.Count(max) << ")";
  } else if (operation == "min") {
      int min = mset.Min();
      std::cout << min << " (x" << mset.Count(min) << ")";
  } else if (operation == "near") {
      int near_num = std::stoi(near);

      if (near[0] == '+') {
        int fl = mset.Ceil(near_num + 1);
        std::cout << fl << " (x" << mset.Count(fl) << ")"; 
      } else if (near[0] == '-') {
          int ceil = mset.Floor((near_num * -1) - 1);
          std::cout << ceil << " (x" << mset.Count(ceil) << ")";
      } else if (isdigit(near[0])) {
          if (mset.Contains(near_num)) {
            std::cout << near_num << " (x" << mset.Count(near_num) << ")";
          } else {
            std::cout << "No match";
          }
      } else {
          std::cout << "Invalid prime";
      }
    } else {
        std::cout << "Command " << "'" << operation << "' is invalid\n";
        std::cout << "Possible commands are: all|min|max|near";
      }
}

int main(int argc, char *argv[]) {
  Multiset<int> factors;

  unsigned int number;
  std::string command;
  std::string near_arg;

  // if (argc != 3) {
  //   std::cout << "Usage: ./prime_factors <number> <command> [<args>]" << std::endl;
  //   exit(1);
  // }

  number = std::stoi(argv[1]);
  command = argv[2];
  near_arg = argv[3];

  PrimeFactors(factors, number);
  PrintFactors(factors, command, near_arg);

  std::cout << std::endl;
}