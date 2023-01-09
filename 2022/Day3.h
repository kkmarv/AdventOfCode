#pragma once

#include <algorithm>
#include <fstream>
#include <vector>

#include <stringUtils.h>

#include "Header.h"

class Day3 : public DayTemplate
{
  private:
    std::ifstream inputFile         = util::readFile("./day3_input.txt");
    std::ifstream testFile          = util::readFile("./day3_test.txt");
    const std::string expectedValP1 = "";
    const std::string expectedValP2 = "";

    // A65 - Z90
    // a97 - z122
    int prio(char c)
    {
        if (c >= 65 && c <= 90)
            return c - 38;
        else if (c >= 96 && c <= 122)
            return c - 96;
        else
            return -1;
    }

  public:
    std::string part1(std::ifstream &inputFile) override
    {
        util::resetStream(inputFile);

        size_t duplicateItemSum = 0;
        std::vector<int> frontCount(53);
        std::vector<int> backCount(53);

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;

            // Get the compartment contents
            std::string frontCompartment = line.substr(0, line.size() / 2);
            std::string backCompartment  = line.substr(line.size() / 2, line.size());

            // Fill vectors with number of occurrences
            for (char c : frontCompartment)
                frontCount[prio(c)]++;
            for (char c : backCompartment)
                backCount[prio(c)]++;

            // If a single character appears twice, count its prio towards the sum
            for (size_t prio = 1; prio < frontCount.size(); ++prio)
                if ((frontCount[prio] > 0) && (backCount[prio] > 0))
                {
                    duplicateItemSum += prio;
                    break;
                }

            // Reset the prio count for the next iteration
            std::fill(frontCount.begin(), frontCount.end(), 0);
            std::fill(backCount.begin(), backCount.end(), 0);
        }

        std::cout << "Sum of the priority of duplicate items: " << duplicateItemSum;

        return;
    }

    // The Pythonic approach
    std::string part2(std::ifstream &) override
    {
        util::resetStream(inputFile);

        int badgeSum = 0;

        // The inventory list of our group of three elves
        std::vector<std::string> batch(3);
        // The vector keeping the common items between elf 1 and 2
        std::vector<char> commonItems1;
        // The vector keeping the common items between elf 2 and 3
        std::vector<char> commonItems2;

        int lineNumber = 0;
        for (std::string line; std::getline(inputFile, line); ++lineNumber)
        {
            if (line.empty())
                continue;

            // Announce a new group of 3 elves
            if (lineNumber % 3 == 0)
                std::cout << "Group: " << lineNumber / 3 + 1 << std::endl;

            // Fill the inventory list from our group
            std::sort(line.begin(), line.end()); // necessary for set_intersection
            batch[lineNumber % 3] = line;
            std::cout << "Elf " << lineNumber % 3 + 1 << ": " << line << std::endl;

            // Keep filling the inventory list until the group is done
            if (lineNumber == 0 || lineNumber % 3 != 2)
                continue;

            // Intersect the inventory of elf 1 with the inventory of elf 2
            std::set_intersection(batch[0].begin(), batch[0].end(), batch[1].begin(), batch[1].end(),
                                  std::back_inserter(commonItems1));

            // Intersect the intersection of elf 1 and 2 with the inventory of elf 3
            std::set_intersection(commonItems1.begin(), commonItems1.end(), batch[2].begin(), batch[2].end(),
                                  std::back_inserter(commonItems2));

            // After intersecting all 3 inventories, the badge is what is left.
            // Now calculate the badge priority
            char badge = commonItems2[0];
            badgeSum += prio(badge);
            std::cout << "Badge: " << badge << " | Priority: " << prio(badge) << " | Sum: " << badgeSum << std::endl
                      << std::endl;

            commonItems1.clear();
            commonItems2.clear();
        }

        std::cout << "Sum of the priority of the badges: " << badgeSum;
    }
};
