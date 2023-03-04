#include "Days.h"

std::string Day4::part1(std::ifstream &inputFile)
{
    util::resetStream(inputFile);

    int totalOverlapSum = 0;

    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

        auto elfSplit      = util::splitString(line, ',');
        int firstElfLower  = std::stoi(util::splitString(elfSplit[0], '-')[0]);
        int firstElfUpper  = std::stoi(util::splitString(elfSplit[0], '-')[1]);
        int secondElfLower = std::stoi(util::splitString(elfSplit[1], '-')[0]);
        int secondElfUpper = std::stoi(util::splitString(elfSplit[1], '-')[1]);

        if (intervalsOverlapTotal(firstElfLower, firstElfUpper, secondElfLower, secondElfUpper))
            totalOverlapSum++;
    }

    return std::to_string(totalOverlapSum);
}

std::string Day4::part2(std::ifstream &inputFile)
{
    util::resetStream(inputFile);

    int anyOverlapSum = 0;

    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

        auto elfSplit      = util::splitString(line, ',');
        int firstElfLower  = std::stoi(util::splitString(elfSplit[0], '-')[0]);
        int firstElfUpper  = std::stoi(util::splitString(elfSplit[0], '-')[1]);
        int secondElfLower = std::stoi(util::splitString(elfSplit[1], '-')[0]);
        int secondElfUpper = std::stoi(util::splitString(elfSplit[1], '-')[1]);

        if (intervalsOverlap(firstElfLower, firstElfUpper, secondElfLower, secondElfUpper))
            anyOverlapSum++;
    }
    return std::to_string(anyOverlapSum);
}

bool Day4::intervalsOverlapTotal(int aLower, int aUpper, int bLower, int bUpper) const
{
    // Case interval a lies within b
    if (aLower >= bLower && aUpper <= bUpper)
        return true;
    // Case interval b lies within a
    else if (bLower >= aLower && bUpper <= aUpper)
        return true;
    return false;
}

bool Day4::intervalsOverlap(int aLower, int aUpper, int bLower, int bUpper) const
{
    // Case interval a leaks into b (seen from left)
    if (aLower >= bLower && aLower <= bUpper)
        return true;
    // Case interval b leaks into a (seen from left)
    else if (bLower >= aLower && bLower <= aUpper)
        return true;
    return false;
}