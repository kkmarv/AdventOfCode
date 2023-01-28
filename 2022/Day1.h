#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include <stringUtils.h>

#include "DayTemplate.h"

class Day1 : public DayTemplate
{
  private:
    std::ifstream inputFile         = util::readFile("./day1_input.txt");
    std::ifstream testFile          = util::readFile("./day1_test.txt");
    const std::string expectedValP1 = "";
    const std::string expectedValP2 = "";

  public:
    std::string part1(std::ifstream &inpitFile) override
    {
        int currentBackpackCalories = 0;
        int backpackCaloriesMax1 = 0, backpackCaloriesMax2 = 0, backpackCaloriesMax3 = 0;

        for (std::string line; std::getline(inputFile, line);)
        {
            // Add calories to the elves backpack.
            if (!line.empty())
            {
                currentBackpackCalories += std::stoi(line);
            }
            // Update the highest amount of calories found
            else
            {
                if (currentBackpackCalories > backpackCaloriesMax1)
                {
                    backpackCaloriesMax3 = backpackCaloriesMax2;
                    backpackCaloriesMax2 = backpackCaloriesMax1;
                    backpackCaloriesMax1 = currentBackpackCalories;
                }
                else if (currentBackpackCalories > backpackCaloriesMax2)
                {
                    backpackCaloriesMax3 = backpackCaloriesMax2;
                    backpackCaloriesMax2 = currentBackpackCalories;
                }
                else if (currentBackpackCalories > backpackCaloriesMax3)
                {
                    backpackCaloriesMax3 = currentBackpackCalories;
                }
                // Reset current backpack content
                currentBackpackCalories = 0;
            }
        }

        std::cout << "Most calories in a single backpack: " << backpackCaloriesMax1 << std::endl;
        std::cout << "Calorie count of the 3 fullest backpacks: "
                  << backpackCaloriesMax1 + backpackCaloriesMax2 + backpackCaloriesMax3;
    }
};