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
        Points rocks = this->parseInputFile(inputFile);

        this->setBorderValues(rocks, false);
        Points sand = this->simulateSandDrops(rocks);
        this->printScan(rocks, sand);

        return std::to_string(sand.size());
    };

    std::string part2(std::ifstream &inputFile) override
    {
        Points rocks = this->parseInputFile(inputFile);

        this->setBorderValues(rocks, true);
        Points sand = this->simulateSandDrops(rocks);
        this->setBorderValues(sand, false);
        this->printScan(rocks, sand);

        return std::to_string(sand.size());
    };

  private:
    const Vec2 SAND_SPAWN_POINT = Vec2{500, 0};

    int yMax = 0;                               // Deepest rock formation
    int xMin = std::numeric_limits<int>::min(); // Furthest rock formation to the left.
    int xMax = std::numeric_limits<int>::max(); // Furthest rock formation to the right.

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
        for (std::string line; std::getline(inputFile, line);) {
            if (line.empty())
                continue;

            std::unique_ptr<Vec2> lastRock = nullptr;
            const auto rockPoints          = util::splitString(line, " -> ");

            for (std::string rockPoint : rockPoints) {
                auto rockCoordinates = util::splitString(rockPoint, ',');
                auto nextRock        = Vec2{std::stoi(rockCoordinates[0]), std::stoi(rockCoordinates[1])};

                // Create a line of rocks.
                if (lastRock) {
                    rocks.push_back(*lastRock);
                    for (const Vec2 &rock : getPointsBetween(*lastRock, nextRock))
                        rocks.push_back(rock);
                    rocks.push_back(nextRock);
                }

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

    /**
     * @brief Prints given cave to console.
     * @param rocks The rock formation.
     * @param sand The sand particles.
     */
    void printScan(const Points &rocks, const Points &sand) const
    {
        if (rocks.empty())
            return;

        // Create the 2D vector of needed size.
        std::vector<std::vector<char>> scannedLayers(yMax + 1, std::vector<char>(xMax - this->xMin + 1, Tile::AIR));
        scannedLayers[SAND_SPAWN_POINT.y][SAND_SPAWN_POINT.x - this->xMin] = Tile::START;

        // Update the scannedLayers with the positions of the rocks.
        for (auto &rock : rocks)
            scannedLayers[rock.y][rock.x - this->xMin] = Tile::ROCK;

        for (auto &sandCorn : sand)
            scannedLayers[sandCorn.y][sandCorn.x - this->xMin] = Tile::SAND;

        // Print the scannedLayers.
        for (const auto &scanLayer : scannedLayers) {
            for (const auto scanResult : scanLayer)
                std::cout << scanResult;
            std::cout << std::endl;
        }
    }

    /**
     * @brief Sets class member values for part 1.
     * @param points The points to extract min and max borders from.
     * @param leaveXBorderUndefined Whether to also set x coordinates.
     */
    void setBorderValues(const Points &points, bool leaveXBorderUndefined)
    {
        this->xMax = leaveXBorderUndefined ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
        this->xMin = leaveXBorderUndefined ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

        for (const auto &point : points) {
            if (point.x < this->xMin)
                this->xMin = point.x;
            if (point.x > this->xMax)
                this->xMax = point.x;
            if (point.y > this->yMax)
                this->yMax = point.y;
        }
    }

    /**
     * @brief Simulate sandCorns dropping from the sandCorn spawn point until the first sandCorn drops out of
     * bounds.
     * @param cave The rocky cave in which to drop rocks.
     * @return The cave after the first sandCorn dropped out of bounds.
     */
    Points simulateSandDrops(const Points &rocks) const
    {
        Points sand;

        while (true) {
            Vec2 sandCorn = SAND_SPAWN_POINT;

            // Find the resting position of the rock.
            while (true) {
                // The sandCorn went out of bounds. (only applicable for part 1)
                if (sandCorn.x < this->xMin || sandCorn.x > this->xMax || sandCorn.y > this->yMax)
                    return sand;

                Vec2 previousState = sandCorn;
                dropSandCorn(sandCorn, sand, rocks);

                // The sandCorn came to rest.
                if (sandCorn == previousState) {
                    util::sortedInsert(sand, sandCorn);

                    // Used for part 2; in part 1 sandCorns never rests at the spawn.
                    if (sandCorn == SAND_SPAWN_POINT)
                        return sand;

                    break;
                }
            }
        }
    }

    void dropSandCorn(Vec2 &sandCorn, const Points &sand, const Points &rocks) const
    {
        // The sandCorn lies on the floor. (part 2)
        if (sandCorn.y + 1 == this->yMax + 2)
            return;

        // Try moving down.
        if (!std::binary_search(rocks.begin(), rocks.end(), sandCorn + Vec2{0, 1}) &&
            !std::binary_search(sand.begin(), sand.end(), sandCorn + Vec2{0, 1}))
            sandCorn += Vec2{0, 1};

        // Try moving down and to the left.
        else if (!std::binary_search(rocks.begin(), rocks.end(), sandCorn + Vec2{-1, 1}) &&
                 !std::binary_search(sand.begin(), sand.end(), sandCorn + Vec2{-1, 1}))
            sandCorn += Vec2{-1, 1};

        // Try moving down and to the right.
        else if (!std::binary_search(rocks.begin(), rocks.end(), sandCorn + Vec2{1, 1}) &&
                 !std::binary_search(sand.begin(), sand.end(), sandCorn + Vec2{1, 1}))
            sandCorn += Vec2{1, 1};
    }
};