#pragma once

#include <iostream>
#include <string>

#include <unitTests.h>

class DayTemplate
{
  public:
    virtual std::string part1(std::ifstream &inputFile) = 0;
    virtual std::string part2(std::ifstream &inputFile) { return ""; };

    virtual std::ifstream &getInputFile() { return this->inputFile; }
    virtual std::ifstream &getTestFile() { return this->testFile; }
    virtual const std::string &getExpectedValP1() const { return this->expectedValP1; }
    virtual const std::string &getExpectedValP2() const { return this->expectedValP2; }

  protected:
    DayTemplate(std::string expectedValP1, std::string expectedValP2, std::string inputFilePath,
                std::string testFilePath)
        : expectedValP1(expectedValP1),
          expectedValP2(expectedValP2),
          inputFile(util::readFile(inputFilePath)),
          testFile(util::readFile(testFilePath))
    {
    }

  private:
    std::ifstream inputFile;
    std::ifstream testFile;
    const std::string expectedValP1;
    const std::string expectedValP2;
};
