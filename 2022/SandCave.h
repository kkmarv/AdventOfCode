#pragma once

#include <cassert>
#include <vector>

#include <stringUtils.h>

struct Vec2
{
    int x; // distance to the right
    int y; // distance downwards
};

enum class Tile : char
{
    START    = '+', // ▼
    AIR      = ' ',
    ROCK     = '#', // █
    SAND     = 'o', // ░
    SANDPATH = '~'
};

class Cave
{
    int sandTileCount = 0;
    int xOffset       = 0;
    inline static const Vec2 sandEntry{500, 0};

    std::vector<std::vector<Tile>> caveCanvas;

    // Init caveCanvas with size read from input data
    // Also set sand spawn point
    void initCaveCanvas(std::ifstream &inputFile)
    {
        int xMin = INT32_MAX, xMax = INT32_MIN, ySize = 0;

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;

            auto readings = util::splitString(line, ' ');

            for (std::string reading : readings)
            {
                if (reading == "->")
                    continue;

                auto coords = util::splitString(reading, ',');
                int xCoord  = std::stoi(coords[0]);
                int yCoord  = std::stoi(coords[1]);

                if (xCoord < xMin)
                    xMin = xCoord;
                else if (xCoord > xMax)
                    xMax = xCoord;
                if (yCoord > ySize)
                    ySize = yCoord;
            }
        }
        util::resetStream(inputFile);
        std::cout << "MIN: " << xMin << " MAX: " << xMax << std::endl;

        // construct the sandCanvas canvas from ySize and xSize.
        // xSize equals the distance between the most distanced rock tiles
        // plus 2 if we want to visualize the path of the falling sand
        // (which may be at the edges, therefore +2)
        int xSize        = (xMax - xMin + 1) + 2;
        this->xOffset    = xMin - 1;
        this->caveCanvas = std::vector<std::vector<Tile>>(ySize + 1, std::vector<Tile>(xSize, Tile::AIR));
        this->caveCanvas[this->sandEntry.y][this->sandEntry.x - this->xOffset] = Tile::START;
    };

    // Create the cave representation from input data
    void parseInput(std::ifstream &inputFile)
    {
        this->initCaveCanvas(inputFile);

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
                continue;

            int lastXCoord = -1, lastYCoord = -1;
            std::vector<std::string> lastCoords;
            auto readings = util::splitString(line, ' ');

            for (std::string &reading : readings)
            {
                if (reading == "->")
                    continue;

                auto coords = util::splitString(reading, ',');
                int xCoord  = std::stoi(coords[0]);
                int yCoord  = std::stoi(coords[1]);

                // We look at the first 2D Point of the reading
                if (lastCoords.empty())
                {
                    lastCoords = coords;
                    lastXCoord = xCoord;
                    lastYCoord = yCoord;
                    continue;
                }

                // Assert that the retrieval of the coords is correct
                // If correct, we should always have one coord that is unchanged
                assert((xCoord == lastXCoord) || (yCoord == lastYCoord));

                this->drawRockWall(Vec2{lastXCoord - this->xOffset, lastYCoord}, Vec2{xCoord - this->xOffset, yCoord});

                // Replace last read values
                lastCoords = coords;
                lastXCoord = xCoord;
                lastYCoord = yCoord;
            }
        }
    };

    // Draws a horizontal or vertical line of rocks onto the canvas
    void drawRockWall(Vec2 start, Vec2 end)
    {
        // horizontal
        if (start.x < end.x)
        { // forwards
            for (int x = start.x; x <= end.x; ++x)
            {
                this->caveCanvas[start.y][x] = Tile::ROCK;
            }
        }
        else
        { // backwards
            for (int x = start.x; x >= end.x; --x)
            {
                this->caveCanvas[start.y][x] = Tile::ROCK;
            }
        }

        // vertical
        if (start.y < end.y)
        { // forwards
            for (int y = start.y; y <= end.y; ++y)
            {
                this->caveCanvas[y][start.x] = Tile::ROCK;
            }
        }
        else
        { // backwards
            for (int y = start.y; y >= end.y; --y)
            {
                this->caveCanvas[y][start.x] = Tile::ROCK;
            }
        }
    }

  public:
    Cave(std::ifstream &inputFile) { this->parseInput(inputFile); };
    void printCave()
    {
        for (auto &caveLayer : this->caveCanvas)
        {
            for (Tile tile : caveLayer)
                std::cout << static_cast<char>(tile);
            std::cout << std::endl;
        }
    };
};

class SandTile
{
};
