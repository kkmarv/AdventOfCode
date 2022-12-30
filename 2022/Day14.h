#pragma once
#include <vector>

#include <stringUtils.h>

#include "Header.h"
#include "SandCave.h"


class Day14 : public DayTemplate {
 public:
  virtual std::string part1(std::ifstream& inputFile) override {
    util::resetStream(inputFile);

    Cave c(inputFile);
    c.printCave();
    
    return "-1";
  };

  virtual std::string part2(std::ifstream& inputFile) override {
    util::resetStream(inputFile);
    return "-1";
  };

  Day14() : DayTemplate("24", "", "day14_input.txt", "day14_test.txt"){};
};