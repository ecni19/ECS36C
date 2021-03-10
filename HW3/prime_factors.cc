#include <iostream>
#include <string>
#include "multiset.h"

// print factors from the multiset depending on operation given
void PrintFactors(Multiset<int> &factors, std::string op, std::string near) {
  // size of 1 means a prime number was given (factors would be 1 and itself)
  if (factors.Size() == 1) {
    std::cerr << "No prime factors\n";
    exit(0);
  }
  // check to see if op (argv[2]) is equal to any of the operations
  if (op == "all") {
    // need to print in ascending order, so start at Min(), end at Max()
    for (int i = factors.Min(); i <= factors.Max(); i++) {
      // continue to next number if i d.n.e in mset
      if (!factors.Contains(i)) {
        continue;
      } else {
        std::cout << i << " (x" << factors.Count(i) << "), ";
      }
    }
    std::cout << '\n';
  } else if (op == "max") {
      std::cout << factors.Max() <<
      " (x" << factors.Count(factors.Max()) << ")";
  } else if (op == "min") {
      std::cout << factors.Min() <<
      " (x" << factors.Count(factors.Min()) << ")";
  } else if (op == "near") {
      int near_prime;  // for storing the additional argument as an int
      if (near.empty()) {  // if no number is specified after "near"
        std::cerr << "Command 'near' expects another argument: [+/-]prime\n";
        exit(1);
      }
      // check first character for +/- to determine which operation
      // check second character for valid number
      if (near[0] == '+' && isdigit(near[1])) {
        near_prime = std::stoi(near);
        if (near_prime < factors.Max()) {
          int ceil = factors.Ceil(near_prime + 1);
          std::cout << ceil << " (x" << factors.Count(ceil) << ")";
        } else {
            std::cout << "No match\n";
            exit(0);
        }
      } else if (near[0] == '-' && isdigit(near[1])) {
          near_prime = -1 * std::stoi(near);
          if (near_prime > factors.Min()) {
            int fl = factors.Floor(near_prime - 1);
            std::cout << fl << " (x" << factors.Count(fl) << ")";
          } else {
              std::cout << "No match\n";
              exit(0);
          }
      } else if (isdigit(near[0])) {
          near_prime = std::stoi(near);
          if (factors.Contains(near_prime)) {
            std::cout << near_prime <<
            " (x" << factors.Count(near_prime) << ")";
          } else {
              std::cout << "No match\n";
              exit(0);
          }
      } else {
          std::cerr << "Invalid prime\n";
          exit(1);
      }
    } else {  // if argv[2] is not a valid operation
        std::cerr << "Command " << "'" << op << "' is invalid\n";
        std::cerr << "Possible commands are: all|min|max|near\n";
        exit(1);
      }
}

// finding and inserting all the prime factors into mset
void FindFactors(Multiset<int> &factors, unsigned int &num) {
  // will keep on dividing by 2 as long as n is even
  // finds how many 2s are in the number.
  while (num % 2 == 0) {
    factors.Insert(2);
    num = num / 2;
  }
  // when n gets here, then it is an odd number
  // start i at 3 and increment by 2 so it is always odd.
  for (unsigned int i = 3; i <= num; i += 2) {
    while (num % i == 0) {
      factors.Insert(i);
      num = num / i;
    }
  }
}

int main(int argc, char *argv[]) {
  Multiset<int> ms;

  unsigned int number;
  std::string command;
  std::string near_arg;

  // checking for at least 3 arguments
  if (argc <= 2) {
    std::cerr << "Usage: " << argv[0] << " <number> <command> [<args>]\n";
    exit(1);
  }
  // check if a number was inputted
  if (isdigit(argv[1][0])) {
    number = std::stoi(argv[1]);
  } else {
      std::cerr << "Invalid number\n";
      exit(1);
  }
  // case if "near" command was not specified
  if (argc == 3) {
    FindFactors(ms, number);
  } else if (argc == 4) {  // case where "near" argument is given
      if (argv[3][0] == '+' || argv[3][0] == '-' || isdigit(argv[3][0])) {
        near_arg = argv[3];  // assign near_arg to argv[3]
      } else {
          std::cerr << "Invalid prime\n";
          exit(1);
      }
      FindFactors(ms, number);
  }

  // will assign argv[2] to command only if all
  // tests above pass
  command = argv[2];

  PrintFactors(ms, command, near_arg);
}
