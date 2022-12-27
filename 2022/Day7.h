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

    Directory* fileSystem  = parseCommands(inputFile);
    size_t diskSpaceNeeded = Directory::diskSpaceForUpgrade - fileSystem->calcFreeSpace();

    // Check directory sizes from task
    // unitTest::assertEquals(fileSystem->getSize(), 48381165Ui64);
    // unitTest::assertEquals(fileSystem->calcFreeSpace(), 21618835Ui64);

    std::vector<Directory*> unvisitedDirs;
    Directory* dirToDelete = fileSystem;
    unvisitedDirs.push_back(fileSystem);

    while (!unvisitedDirs.empty()) {
      Directory* curDir = unvisitedDirs.back();
      unvisitedDirs.pop_back();

      // Abort if dir with perfect size fit is found
      if (curDir->getSize() == diskSpaceNeeded)
        return std::to_string(curDir->getSize());

      // Update currently visited dir
      if (curDir->getSize() > diskSpaceNeeded && curDir->getSize() < dirToDelete->getSize()) {
        dirToDelete = (Directory*)curDir;
      }

      // Refill the queue
      for (DiskContent* dc : curDir->getContent()) {
        if (dc->isDir()) {
          unvisitedDirs.push_back((Directory*)dc);
        }
      }
    }

    return std::to_string(dirToDelete->getSize());
  }

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
};