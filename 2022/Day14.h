#pragma once
#include <vector>

#include <algorithm>
#include <limits>
#include <memory>

#include <stringUtils.h>
#include <vectorUtils.h>

#include "DayTemplate.h"
#include "SandCave.h"

using Points = std::vector<Vec2>;

class Day14 : public DayTemplate<Points>
{
  public:
    ~Day14() override = default;
    Day14() : DayTemplate("24", "93", "day14_input.txt", "day14_test.txt") {}

    std::string part1(std::ifstream &inputFile) override
    {
        const Points rocks      = parseInputFile(inputFile);
        const Border rockBorder = getBorder(rocks);
        const Points sand       = simulateSandDrops(rocks, rockBorder, Part::ONE);

        printScan(rocks, sand, rockBorder);

        return std::to_string(sand.size());
    };

    std::string part2(std::ifstream &inputFile) override
    {
        const Points rocks       = parseInputFile(inputFile);
        const Points sand        = simulateSandDrops(rocks, getBorder(rocks, true), Part::TWO);
        const Border rockBorder  = getBorder(rocks);
        const Border sandBorder  = getBorder(sand);
        const Border printBorder = {std::min(rockBorder.xMin, sandBorder.xMin),
                                    std::max(rockBorder.xMax, sandBorder.xMax),
                                    std::max(rockBorder.yMax, sandBorder.yMax)};

        printScan(rocks, sand, printBorder);

        return std::to_string(sand.size());
    };

  private:
    const Vec2 SAND_SPAWN_POINT = Vec2{500, 0};

    /**
     * @brief Parse the task cave from given ifstream and create a vector which contains all rock coordinates as
     * Vec2 objetcs. Resolve the end Points from task input to real coordinates on the way.
     * @param inputFile The file which to parse.
     * @return An unordered vector of Vec2 objects representing all cave.
     */
    Points parseInputFile(std::ifstream &inputFile) override
    {
        Points rocks;

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
                auto nextRock        = Vec2{std::stoi(rockCoordinates[0]), std::stoi(rockCoordinates[1])};

                if (!lastRock)
                {
                    lastRock = std::make_unique<Vec2>(nextRock);
                    continue;
                }

                // Create a line of rocks.
                rocks.push_back(*lastRock);
                for (const Vec2 &rock : getPointsBetween(*lastRock, nextRock))
                    rocks.push_back(rock);
                rocks.push_back(nextRock);

                lastRock = std::make_unique<Vec2>(nextRock);
            }
        }

        std::sort(rocks.begin(), rocks.end());
        return rocks;
    }

    /**
     * @brief Create a Vector of all Vec2 objects that are between two given Points.
     * @param start The start Vec2 object.
     * @param end The end Vec2 object.
     * @return A vector of 2D Points the are between start and end.
     */
    Points getPointsBetween(const Vec2 &start, const Vec2 &end) const
    {
        Points result;

        // Insert Points along x axis
        if (start.x < end.x)
            for (int x = start.x; x < end.x; ++x)
                result.emplace_back(x, end.y);
        else if (start.x > end.x)
            for (int x = start.x; x > end.x; --x)
                result.emplace_back(x, end.y);

        // Insert Points along y axis
        if (start.y < end.y)
            for (int y = start.y; y < end.y; ++y)
                result.emplace_back(end.x, y);
        else if (start.y > end.y)
            for (int y = start.y; y > end.y; --y)
                result.emplace_back(end.x, y);

        return result;
    }

    Border getBorder(const Points &points, const bool leaveXBorderUndefined = false) const
    {
        int yMax = 0;
        int xMin = leaveXBorderUndefined ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        int xMax = leaveXBorderUndefined ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();

        for (const auto &point : points)
        {
            if (point.x < xMin)
                xMin = point.x;
            if (point.x > xMax)
                xMax = point.x;
            if (point.y > yMax)
                yMax = point.y;
        }

        return {xMin, xMax, yMax};
    }

    /**
     * @brief Prints given cave to console.
     * @param rocks The rock formation.
     * @param sand The sand particles.
     */
    void printScan(const Points &rocks, const Points &sand, const Border &border) const
    {
        // Create the 2D vector of needed size.
        std::vector<std::vector<char>> scannedLayers(border.yMax + 1,
                                                     std::vector<char>(border.xMax - border.xMin + 1, Tile::AIR));

        scannedLayers[SAND_SPAWN_POINT.y][SAND_SPAWN_POINT.x - border.xMin] = Tile::START;

        // Update the scannedLayers with the positions of the rocks.
        for (auto &rock : rocks)
            scannedLayers[rock.y][rock.x - border.xMin] = Tile::ROCK;

        for (auto &sandCorn : sand)
            scannedLayers[sandCorn.y][sandCorn.x - border.xMin] = Tile::SAND;

        // Print the scannedLayers.
        for (const auto &scanLayer : scannedLayers)
        {
            for (const auto scanResult : scanLayer)
                std::cout << scanResult;
            std::cout << std::endl;
        }
    }

    /**
     * @brief Simulate sandCorns dropping from the spawn point until the first sandCorn drops out bounds.
     * @param cave The rocky cave in which to drop rocks.
     * @return The cave after the first sandCorn dropped out of bounds.
     */
    Points simulateSandDrops(const Points &rocks, const Border &border, Part part) const
    {
        Points sand;

        while (true)
        {
            Vec2 sandCorn = SAND_SPAWN_POINT;

            // Find the resting position of the rock.
            while (true)
            {
                // The sandCorn went out of its horizontal bounds.
                if (sandCorn.x < border.xMin || sandCorn.x > border.xMax)
                    return sand;

                // In part 1, the sand is not allowed to move past the last rock.
                if (part == Part::ONE && sandCorn.y >= border.yMax)
                    return sand;

                // In part 2, the sand has to move one line past the last rock.
                if (part == Part::TWO && sandCorn.y > border.yMax + 1)
                    return sand;

                Vec2 previousState = sandCorn;
                dropSandCorn(sandCorn, sand, rocks, border);

                // The sandCorn came to rest.
                if (sandCorn == previousState)
                {
                    util::sortedInsert(sand, sandCorn);

                    // Used for part 2; in part 1, sandCorns never rests at the spawn.
                    if (sandCorn == SAND_SPAWN_POINT)
                        return sand;

                    break;
                }
            }
        }
    }

    /**
     * @brief Updates the position of the sandCorn if the path is free.
     * @param sandCorn A sandCorn.
     * @param sand An ordered vector of sandCorns.
     * @param rocks An ordered vector of rocks.
     * @param border The borders to be respected.
     */
    void dropSandCorn(Vec2 &sandCorn, const Points &sand, const Points &rocks, const Border &border) const
    {
        // The sandCorn lies on the cave floor. (part 2)
        if (sandCorn.y == border.yMax + 1)
            return;

        // Try moving down.
        else if (isPointFree(sandCorn + Vec2{0, 1}, rocks, sand))
            sandCorn += Vec2{0, 1};

        // Try moving down and to the left.
        else if (isPointFree(sandCorn + Vec2{-1, 1}, rocks, sand))
            sandCorn += Vec2{-1, 1};

        // Try moving down and to the right.
        else if (isPointFree(sandCorn + Vec2{1, 1}, rocks, sand))
            sandCorn += Vec2{1, 1};
    }

    /**
     * @brief Checks if given point already is in one of the given vectors.
     * @param point The point to check.
     * @param rocks An ordered vector of sandCorns.
     * @param sand An ordered vector of sandCorns.
     * @return True if given point does not exist in the vectors.
     */
    bool isPointFree(const Vec2 &point, const Points &rocks, const Points &sand) const
    {
        return !std::binary_search(rocks.begin(), rocks.end(), point) &&
               !std::binary_search(sand.begin(), sand.end(), point);
    }
};