#include <iostream>
#include <string>

#include "stringUtils.h"
#include "unitTests.h"

namespace Template {

   // Solution to part 1
   int part1(std::ifstream& inputFile) {
      util::resetStream(inputFile);

      for (std::string line; std::getline(inputFile, line);) {
         if (line.empty())
            continue;
      }

      return -1;
   }

   // Solution to part 2
   int part2(std::ifstream& inputFile) {
      util::resetStream(inputFile);

      for (std::string line; std::getline(inputFile, line);) {
         if (line.empty())
            continue;
      }

      return -1;
   }

   int main() {
      auto inputFile = util::readFile("./input.txt");
      auto testFile = util::readFile("./test.txt");

      unitTest::assertEquals(part1(testFile), -1, "Part 1");
      unitTest::assertEquals(part2(testFile), -1, "Part 2");

      part1(inputFile);
      part2(inputFile);

      return 0;
   }
}