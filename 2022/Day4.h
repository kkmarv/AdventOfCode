#pragma once

#include <stringUtils.h>

#include "Header.h"


class Day4 : public DayTemplate {
 private:
  std::ifstream inputFile         = util::readFile("./day4_input.txt");
  std::ifstream testFile          = util::readFile("./day4_test.txt");
  const std::string expectedValP1 = "";
  const std::string expectedValP2 = "";


  bool intervalsOverlapTotal(int aLower, int aUpper, int bLower, int bUpper) {
    // Case interval a lies within b
    if (aLower >= bLower && aUpper <= bUpper)
      return true;
    // Case interval b lies within a
    else if (bLower >= aLower && bUpper <= aUpper)
      return true;
    return false;
  }

  bool intervalsOverlap(int aLower, int aUpper, int bLower, int bUpper) {
    // Case interval a leaks into b (seen from left)
    if (aLower >= bLower && aLower <= bUpper)
      return true;
    // Case interval b leaks into a (seen from left)
    else if (bLower >= aLower && bLower <= aUpper)
      return true;
    return false;
  }

 public:
  void main(std::ifstream& inputFile,
            std::ifstream& testFile,
            const std::string& expectedValP1,
            const std::string& expectedValP2) {
    std::ifstream inputFile("./input.txt");

    if (!inputFile.is_open()) {
      std::cout << "File could not be opened.";
      return;
    }

    int totalOverlapSum = 0;
    int anyOverlapSum   = 0;

    for (std::string line; std::getline(inputFile, line);) {
      if (line.empty())
        continue;

      auto elfSplit      = util::splitString(line, ',');
      int firstElfLower  = std::stoi(util::splitString(elfSplit[0], '-')[0]);
      int firstElfUpper  = std::stoi(util::splitString(elfSplit[0], '-')[1]);
      int secondElfLower = std::stoi(util::splitString(elfSplit[1], '-')[0]);
      int secondElfUpper = std::stoi(util::splitString(elfSplit[1], '-')[1]);

      if (intervalsOverlapTotal(firstElfLower, firstElfUpper, secondElfLower, secondElfUpper))
        totalOverlapSum++;
      if (intervalsOverlap(firstElfLower, firstElfUpper, secondElfLower, secondElfUpper))
        anyOverlapSum++;
    }

    std::cout << "Number of total overlaps: " << totalOverlapSum << std::endl;
    std::cout << "Number of overlaps: " << anyOverlapSum << std::endl;
  }
};