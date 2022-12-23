#pragma once

#include <algorithm>
#include <deque>

#include <stringUtils.h>

#include "Header.h"

using std::cout;


class Day5 : DayTemplate {
 private:
  const std::ifstream inputFile   = util::readFile("./day5_input.txt");
  const std::ifstream testFile    = util::readFile("./day5_test.txt");
  const std::string expectedValP1 = "CMZ";
  const std::string expectedValP2 = "MCD";


  void moveCrates(std::vector<std::deque<char>>& storagePlaces, int count, int from, int to) {
    for (int i = 0; i < count; i++) {
      storagePlaces[to].push_back(storagePlaces[from].back());
      storagePlaces[from].pop_back();
    }
  }

  void moveMultipleCrates(std::vector<std::deque<char>>& storagePlaces, int count, int from, int to) {
    std::copy(storagePlaces[from].end() - count, storagePlaces[from].end(), std::back_inserter(storagePlaces[to]));
    storagePlaces[from].resize(storagePlaces[from].size() - count);
  }

  void printStorage(const std::vector<std::deque<char>>& storagePlaces) {
    for (size_t i = 0; i < storagePlaces.size(); ++i) {
      cout << i + 1 << ' ';
      for (char crate : storagePlaces[i])
        cout << '[' << crate << "] ";
      cout << std::endl;
    }
  }


 public:
  std::string part1(std::ifstream& inputFile) override {
    std::vector<std::deque<char>> storagePlaces;

    // Read the stacks
    for (std::string line; std::getline(inputFile, line);) {
      if (line.empty())
        break;

      // TODO look into resize/reserve vector
      // Initialize crate stacks (runs only once)
      while (storagePlaces.size() < line.size() / 4 + 1)
        storagePlaces.push_back(std::deque<char>());

      // Read every 4th element and assign it to its corresponding stack
      for (size_t col = 1; col < line.size(); col += 4) {
        if (std::isalpha(line[col])) {
          auto& crateQueue = storagePlaces[col / 4];
          crateQueue.push_front(line[col]);
        }
      }
    }

    cout << "Start configuration:" << std::endl;
    printStorage(storagePlaces);
    cout << std::endl;

    // Read the commands
    for (std::string line; std::getline(inputFile, line);) {
      if (line.empty())
        continue;

      auto commandSplit = util::splitString(line, ' ');

      moveCrates(storagePlaces, std::stoi(commandSplit[1]), std::stoi(commandSplit[3]) - 1,
                 std::stoi(commandSplit[5]) - 1);
    }

    cout << "End configuration:" << std::endl;
    printStorage(storagePlaces);
    cout << std::endl;

    std::string result;
    cout << "The top crates after sorting are: ";
    for (auto s : storagePlaces) {
      result += s.back();
      cout << s.back();
    }
    cout << std::endl;

    return result;
  }

  std::string part2(std::ifstream& inputFile) override {
    std::vector<std::deque<char>> storagePlaces;

    // Read the stacks
    for (std::string line; std::getline(inputFile, line);) {
      if (line.empty())
        break;

      // Initialize crate stacks (runs only once)
      while (storagePlaces.size() < line.size() / 4 + 1)
        storagePlaces.push_back(std::deque<char>());

      // Read every 4th element and assign it to its corresponding stack
      for (size_t col = 1; col < line.size(); col += 4) {
        if (std::isalpha(line[col])) {
          auto& crateStack = storagePlaces[col / 4];
          crateStack.push_front(line[col]);
        }
      }
    }

    cout << "Start configuration:" << std::endl;
    printStorage(storagePlaces);
    cout << std::endl;

    // Read the commands
    for (std::string line; std::getline(inputFile, line);) {
      if (line.empty())
        continue;

      auto commandSplit = util::splitString(line, ' ');

      moveMultipleCrates(storagePlaces, std::stoi(commandSplit[1]), std::stoi(commandSplit[3]) - 1,
                         std::stoi(commandSplit[5]) - 1);
    }

    cout << "End configuration:" << std::endl;
    printStorage(storagePlaces);
    cout << std::endl;

    std::string result;
    cout << "The top crates after sorting are: ";
    for (auto s : storagePlaces) {
      result += s.back();
      cout << s.back();
    }
    cout << std::endl;

    return result;
  }
};