#pragma once

#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <stringUtils.h>
#include <vectorUtils.h>

#include "DiskContent.h"
#include "SandCave.h"

template <typename DataType, typename ParsedDataType> class DayBase
{
  public:
    /**
     * @brief
     * @param inputFile The path to a file containing the day's input data.
     * @return The solution to part 1.
     */
    virtual std::string part1(std::ifstream &inputFile) = 0;

    /**
     * @brief
     * @param inputFile A path to the file containing the day's input data.
     * @return The solution to part 2.
     */
    virtual std::string part2(std::ifstream &inputFile) = 0;

    virtual std::ifstream &getInputFile() { return this->inputFile; };
    virtual std::ifstream &getTestFile() { return this->testFile; };
    virtual const std::string &getExpectedValuePart1() const { return this->expectedValP1; }
    virtual const std::string &getExpectedValuePart2() const { return this->expectedValP2; }

  private:
    std::ifstream inputFile;
    std::ifstream testFile;
    const std::string expectedValP1;
    const std::string expectedValP2;

  protected:
    /**
     * @brief
     * @param expectedValP1 The expected output value for the part 1 test case.
     * @param expectedValP2 The expected output value for the part 2 test case.
     * @param inputFilePath A path to the task input file.
     * @param testFilePath A path to a file containing test data.
     */
    DayBase(const std::string &expectedValP1,
            const std::string &expectedValP2,
            const std::string &inputFilePath,
            const std::string &testFilePath) :
        inputFile(util::readFile(inputFilePath)),
        testFile(util::readFile(testFilePath)),
        expectedValP1(expectedValP1),
        expectedValP2(expectedValP2)
    {
    }

    virtual ~DayBase() = default;

    virtual ParsedDataType parseInputFile(std::ifstream &inputFile) = 0;

    enum class Part
    {
        ONE,
        TWO
    };
};

class Day1 : public DayBase<std::string, void>
{
  public:
    Day1() : DayBase("", "", "./day1_input.txt", "./day1_test.txt") {}
    ~Day1() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;
};

class Day2 : public DayBase<std::string, void>
{
  public:
    Day2() : DayBase("", "", "./day2_input.txt", "./day2_test.txt") {}
    ~Day2() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    static enum Move
    {
        ROCK     = 1,
        PAPER    = 2,
        SCISSORS = 3
    };
    static enum Outcome
    {
        LOSE = 0,
        DRAW = 3,
        WIN  = 6
    };
};

class Day3 : public DayBase<std::string, void>
{
  public:
    Day3() : DayBase("", "", "./day3_input.txt", "./day3_test.txt") {}
    ~Day3() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    int prio(char c) const;
};

class Day4 : public DayBase<std::string, void>
{
  public:
    Day4() : DayBase("", "", "./day4_input.txt", "./day4_test.txt") {}
    ~Day4() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    bool intervalsOverlapTotal(int aLower, int aUpper, int bLower, int bUpper) const;
    bool intervalsOverlap(int aLower, int aUpper, int bLower, int bUpper) const;
};

class Day5 : public DayBase<std::string, void>
{
  public:
    Day5() : DayBase("CMZ", "MCD", "./day5_input.txt", "./day5_test.txt") {}
    ~Day5() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    void moveCrates(std::vector<std::deque<char>> &storagePlaces, int count, int from, int to);
    void moveMultipleCrates(std::vector<std::deque<char>> &storagePlaces, int count, int from, int to);
    void printStorage(const std::vector<std::deque<char>> &storagePlaces);
};

class Day6 : public DayBase<std::string, std::vector<std::string>>
{
  public:
    Day6() : DayBase("7 5 6 10 11 ", "19 23 23 29 26 ", "./day6_input.txt", "./day6_test.txt") {}
    ~Day6() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;
    std::vector<std::string> parseInputFile(std::ifstream &inputFile) override;

  private:
    std::string findMessageStart(const std::string &message, const int window_size) const;
};

class Day7 : public DayBase<std::string, void>
{
  public:
    Day7() : DayBase("95437", "24933642", "./day7_input.txt", "./day7_test.txt") {}
    ~Day7() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    Directory *parseCommands(std::ifstream &inputFile);
    size_t sum(const Directory &directory);
};

class Day14 : public DayBase<std::vector<Vec2>, std::vector<Vec2>>
{
  public:
    using Points = std::vector<Vec2>;

    Day14() : DayBase("24", "93", "day14_input.txt", "day14_test.txt") {}
    ~Day14() override = default;
    std::string part1(std::ifstream &inputFile) override;
    std::string part2(std::ifstream &inputFile) override;

  private:
    const Vec2 SAND_SPAWN_POINT = Vec2{500, 0};

    Points parseInputFile(std::ifstream &inputFile) override;
    Points getPointsBetween(const Vec2 &start, const Vec2 &end) const;
    Border getBorder(const Points &points, const bool leaveXBorderUndefined) const;
    Points simulateSandDrops(const Points &rocks, const Border &border, Part part) const;
    void dropSandCorn(Vec2 &sandCorn, const Points &sand, const Points &rocks, const Border &border, Part part) const;
    bool isPointFree(const Vec2 &point, const Points &rocks, const Points &sand) const;
    void printScan(const Points &rocks, const Points &sand, const Border &border) const;
};
