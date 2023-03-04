#include "Days.h"

std::string Day1::part1(std::ifstream &inputFile)
{
    int currentBackpackCalories = 0;
    int backpackCaloriesMax1    = 0;
    int backpackCaloriesMax2    = 0;
    int backpackCaloriesMax3    = 0;

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

    return "Most calories in a single backpack: " + std::to_string(backpackCaloriesMax1) +
           "Calorie count of the 3 fullest backpacks: " + std::to_string(backpackCaloriesMax1) + " " +
           std::to_string(backpackCaloriesMax2) + " " + std::to_string(backpackCaloriesMax3);
}

std::string Day1::part2(std::ifstream &inputFile) {}
