#pragma once

#include <algorithm>
#include <fstream>

#include <stringUtils.h>

#include "DayTemplate.h"

class Day6 : public DayTemplate
{
  private:
    std::ifstream inputFile         = util::readFile("./day6_input.txt");
    std::ifstream testFile          = util::readFile("./day6_test.txt");
    const std::string expectedValP1 = "";
    const std::string expectedValP2 = "";

  public:
    std::string part1(std::ifstream &inputFile) override
    {
        util::resetStream(inputFile);

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;

            std::vector<char> scramble(4);

            for (size_t pos = 0; pos < line.size(); ++pos)
            {
                auto it = std::adjacent_find(scramble.begin(), scramble.end());

                // No duplicates in vector
                if (it == scramble.end() && scramble.size() != 4)
                    return std::to_string(pos);
                else
                    scramble.clear();

                scramble.push_back(line[pos]);
            }
        }
        return "";
    }

    std::string part2(std::ifstream &inputFile) override
    {
        util::resetStream(inputFile);

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;
        }

        return "";
    }
};