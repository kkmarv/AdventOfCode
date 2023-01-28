#pragma once
#include <vector>

#include <algorithm>
#include <limits>
#include <memory>

#include <stringUtils.h>

#include "DayTemplate.h"
#include "SandCave.h"

class Day14 : public DayTemplate
{
  public:
    Day14() : DayTemplate("24", "", "day14_input.txt", "day14_test.txt"){};

    virtual std::string part1(std::ifstream &inputFile) override
    {
        auto rocks = this->parseInputFile(inputFile);
        this->setBorderValues(rocks);
        auto sand = this->simulateSandDrops(rocks);
        this->printScan(rocks, sand);

        return std::to_string(sand.size());
    };

    virtual std::string part2(std::ifstream &inputFile) override
    {
        util::resetStream(inputFile);
        return "-1";
    };

  private:
    int yMax = 0;
    int xMin = std::numeric_limits<int>::max();
    int xMax = std::numeric_limits<int>::min();

    const Vec2 SAND_SPAWN_POINT = Vec2{500, 0};

    /**
     * @brief Parse the task cave from given istream and create a vector which contains all rock coordinates as
     * Vec2 objetcs. Resolve the end points from task input to real coordinates on the way.
     * @param inputFile The file which to parse.
     * @return An unordered vector of Vec2 objects representing all cave.
     */
    std::vector<Vec2> parseInputFile(std::ifstream &inputFile) const
    {
        std::vector<Vec2> rocks;

        // Being cautious and resetting the stream just in case someone has tampered with insertionIndex before.
        util::resetStream(inputFile);
        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;

            std::unique_ptr<Vec2> lastRock = nullptr;
            const auto rockPoints          = util::splitString(line, " -> ");

            for (std::string rockPoint : rockPoints)
            {
                auto rockCoordinates = util::splitString(rockPoint, ',');
                Vec2 nextRock        = Vec2{std::stoi(rockCoordinates[0]), std::stoi(rockCoordinates[1])};

                // Create a line of rocks.
                if (lastRock)
                {
                    rocks.push_back(*lastRock);
                    for (Vec2 rock : getPointsBetween(*lastRock, nextRock))
                        rocks.push_back(rock);
                    rocks.push_back(nextRock);
                }

                lastRock = std::make_unique<Vec2>(nextRock);
            }
        }
        return rocks;
    }

    /**
     * @brief Create a Vector of all Vec2 objects that are between two given points.
     * @param start The start Vec2 object.
     * @param end The end Vec2 object.
     * @return A vector of 2D points the are between start and end.
     */
    std::vector<Vec2> getPointsBetween(const Vec2 &start, const Vec2 &end) const
    {
        std::vector<Vec2> result;

        // Insert points along x axis
        if (start.x < end.x)
            for (int x = start.x; x < end.x; ++x)
                result.emplace_back(x, end.y);
        else if (start.x > end.x)
            for (int x = start.x; x > end.x; --x)
                result.emplace_back(x, end.y);

        // Insert points along y axis
        if (start.y < end.y)
            for (int y = start.y; y < end.y; ++y)
                result.emplace_back(end.x, y);
        else if (start.y > end.y)
            for (int y = start.y; y > end.y; --y)
                result.emplace_back(end.x, y);

        return result;
    }

    /**
     * @brief Prints given cave to console.
     * @param cave The rocky cave.
     */
    const void printScan(const std::vector<Vec2> &rocks, const std::vector<Vec2> &sand) const
    {
        // Create the 2D vector of needed size.
        std::vector<std::vector<char>> scannedLayers(yMax + 1, std::vector<char>(xMax - xMin + 1, Tile::AIR));
        scannedLayers[SAND_SPAWN_POINT.y][SAND_SPAWN_POINT.x - xMin] = Tile::START;

        // Update the scannedLayers with the positions of the rocks.
        for (auto &rock : rocks)
            scannedLayers[rock.y][rock.x - xMin] = Tile::ROCK;

        for (auto &sandCorn : sand)
            scannedLayers[sandCorn.y][sandCorn.x - xMin] = Tile::SAND;

        // Print the scannedLayers.
        for (auto &scanLayer : scannedLayers)
        {
            for (auto scanResult : scanLayer)
                std::cout << scanResult;
            std::cout << std::endl;
        }
    }

    /**
     * @brief Sets class member values for border values of the cave.
     * @param vector The rocky cave.
     */
    void setBorderValues(const std::vector<Vec2> &rocks)
    {
        for (auto &rock : rocks)
        {
            if (rock.x < this->xMin)
                this->xMin = rock.x;
            if (rock.x > this->xMax)
                this->xMax = rock.x;
            if (rock.y > this->yMax)
                this->yMax = rock.y;
        }
    }

    /**
     * @brief Simulate sand dropping from the sand spawn point until the first sand corn drops out of bounds.
     * @param cave The rocky cave in which to drop sand.
     * @return The cave after the first sand corn dropped out of bounds.
     */
    std::vector<Vec2> simulateSandDrops(std::vector<Vec2> cave) const
    {
        std::vector<Vec2> sand;
        std::sort(cave.begin(), cave.end());

        while (true)
        {
            Vec2 sandCorn = SAND_SPAWN_POINT;

            // Find the resting position of the sandCorn.
            while (true)
            {
                // The sandCorn went out of bounds.
                if (sandCorn.x < this->xMin || sandCorn.x > this->xMax || sandCorn.y > this->yMax)
                    return sand;

                // Try moving down.
                if (std::find(cave.begin(), cave.end(), sandCorn + Vec2{0, 1}) == cave.end() &&
                    std::find(sand.begin(), sand.end(), sandCorn + Vec2{0, 1}) == sand.end())
                    sandCorn++;

                // Try moving down and to the left.
                else if (std::find(cave.begin(), cave.end(), sandCorn + Vec2{-1, 1}) == cave.end() &&
                         std::find(sand.begin(), sand.end(), sandCorn + Vec2{-1, 1}) == sand.end())
                    sandCorn = sandCorn + Vec2{-1, 1};

                // Try moving down and to the right.
                else if (std::find(cave.begin(), cave.end(), sandCorn + Vec2{1, 1}) == cave.end() &&
                         std::find(sand.begin(), sand.end(), sandCorn + Vec2{1, 1}) == sand.end())
                    sandCorn = sandCorn + Vec2{1, 1};

                // The sandCorn came to rest.
                else
                {
                    auto insertionIndex = std::upper_bound(sand.cbegin(), sand.cend(), sandCorn);
                    sand.insert(insertionIndex, sandCorn);
                    break;
                }
            }
        }
    }
};