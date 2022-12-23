#pragma once

#include <iostream>
#include <string>

#include <shortcuts.h>
#include <stringUtils.h>
#include <unitTests.h>

#include "DiskContent.h"
#include "Header.h"


class Day7 : public DayTemplate {
 public:
  Day7() : DayTemplate("95437", "24933642", "./day7_input.txt", "./day7_test.txt") {}

  std::string part1(std::ifstream& inputFile) override {
    util::resetStream(inputFile);

    Directory* fileSystem = parseCommands(inputFile);
    // fileSystem->ls(true); // Uncomment to print Directory structure

    return std::to_string(sum(*fileSystem));
  }

  std::string part2(std::ifstream& inputFile) override {
    util::resetStream(inputFile);

    Directory* fileSystem = parseCommands(inputFile);
    const int unusedSpace = Day7::maxFileSystemSize - fileSystem->getSize();

    return std::to_string(rawr(*fileSystem, unusedSpace));
  }

 private:
  static const int maxFileSystemSize = 70'000'000;
  static const int minUnsedSpace     = 30'000'000;
  static const int maxUsedSpace      = maxFileSystemSize - minUnsedSpace;


  Directory* parseCommands(std::ifstream& inputFile) {
    Directory* root    = new Directory("/");
    Directory* current = root;

    for (std::string line; std::getline(inputFile, line);) {
      // Skip unmeaningful lines:
      // First command should always be cd to root dir
      // Ignore ls commands
      if (line.empty() || line == "$ cd /" || line == "$ ls")
        continue;

      auto prompt = util::splitString(line, ' ');

      // Handle cd command
      if (prompt[0] == "$" && prompt[1] == "cd") {
        if (prompt[2] == "..") {
          current = &(current->getParent());
        } else {
          current = current->findDir(prompt[2]);
        }
      }

      // ls output: directory
      else if (prompt[0] == "dir") {
        Directory* d = new Directory(prompt[1], *current);
        current->add(*d);
      }

      // ls output: file
      else {
        File* f = new File(prompt[1], std::stoull(prompt[0]));
        current->add(*f);
      }
    }

    return root;
  }

  size_t sum(const Directory& directory) {
    size_t sizeSum = 0;

    if (directory.getSize() <= 100'000)
      sizeSum += directory.getSize();

    for (DiskContent* diskContent : directory.getContent()) {
      if (diskContent->isDir())
        sizeSum += sum((Directory&)*diskContent);
    }

    return sizeSum;
  }

  size_t rawr(const Directory& directory, const int usedSpace) {
    size_t spaceSavings = directory.getSize();

    if (directory.getContent().empty()) {
      if (directory.getSize() <= Day7::minUnsedSpace)  // TODO
        return -1;  // This should only occur when there is no dir that is small enough
      return spaceSavings;
    }

    // Find smallest dir in current dir
    for (DiskContent* diskContent : directory.getContent()) {
      if (diskContent->isDir()) {
        size_t childDirSavings = diskContent->getSize();

        if (usedSpace - childDirSavings >= usedSpace - spaceSavings)  // TODO
          spaceSavings = rawr((Directory&)*diskContent, usedSpace);
      }
    }

    return spaceSavings;
  }
};