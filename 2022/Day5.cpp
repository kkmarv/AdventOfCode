#include "Days.h"

std::string Day5::part1(std::ifstream &inputFile)
{
    std::vector<std::deque<char>> storagePlaces;

    // Read the stacks
    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            break;

        // TODO look into resize/reserve vector
        // Initialize crate stacks (runs only once)
        while (storagePlaces.size() < line.size() / 4 + 1)
            storagePlaces.push_back(std::deque<char>());

        // Read every 4th element and assign it to its corresponding stack
        for (size_t col = 1; col < line.size(); col += 4)
        {
            if (std::isalpha(line[col]))
            {
                auto &crateQueue = storagePlaces[col / 4];
                crateQueue.push_front(line[col]);
            }
        }
    }

    std::cout << "Start configuration:" << std::endl;
    printStorage(storagePlaces);
    std::cout << std::endl;

    // Read the commands
    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

        auto commandSplit = util::splitString(line, ' ');

        moveCrates(
            storagePlaces, std::stoi(commandSplit[1]), std::stoi(commandSplit[3]) - 1, std::stoi(commandSplit[5]) - 1);
    }

    std::cout << "End configuration:" << std::endl;
    printStorage(storagePlaces);
    std::cout << std::endl;

    std::string result;
    std::cout << "The top crates after sorting are: ";
    for (auto s : storagePlaces)
    {
        result += s.back();
        std::cout << s.back();
    }
    std::cout << std::endl;

    return result;
}

std::string Day5::part2(std::ifstream &inputFile)
{
    std::vector<std::deque<char>> storagePlaces;

    // Read the stacks
    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            break;

        // Initialize crate stacks (runs only once)
        while (storagePlaces.size() < line.size() / 4 + 1)
            storagePlaces.push_back(std::deque<char>());

        // Read every 4th element and assign it to its corresponding stack
        for (size_t col = 1; col < line.size(); col += 4)
        {
            if (std::isalpha(line[col]))
            {
                auto &crateStack = storagePlaces[col / 4];
                crateStack.push_front(line[col]);
            }
        }
    }

    std::cout << "Start configuration:" << std::endl;
    printStorage(storagePlaces);
    std::cout << std::endl;

    // Read the commands
    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

        auto commandSplit = util::splitString(line, ' ');

        moveMultipleCrates(
            storagePlaces, std::stoi(commandSplit[1]), std::stoi(commandSplit[3]) - 1, std::stoi(commandSplit[5]) - 1);
    }

    std::cout << "End configuration:" << std::endl;
    printStorage(storagePlaces);
    std::cout << std::endl;

    std::string result;
    std::cout << "The top crates after sorting are: ";
    for (auto s : storagePlaces)
    {
        result += s.back();
        std::cout << s.back();
    }
    std::cout << std::endl;

    return result;
}

void Day5::moveCrates(std::vector<std::deque<char>> &storagePlaces, int count, int from, int to)
{
    for (int i = 0; i < count; i++)
    {
        storagePlaces[to].push_back(storagePlaces[from].back());
        storagePlaces[from].pop_back();
    }
}

void Day5::moveMultipleCrates(std::vector<std::deque<char>> &storagePlaces, int count, int from, int to)
{
    std::copy(storagePlaces[from].end() - count, storagePlaces[from].end(), std::back_inserter(storagePlaces[to]));
    storagePlaces[from].resize(storagePlaces[from].size() - count);
}

void Day5::printStorage(const std::vector<std::deque<char>> &storagePlaces)
{
    for (size_t i = 0; i < storagePlaces.size(); ++i)
    {
        std::cout << i + 1 << ' ';
        for (char crate : storagePlaces[i])
            std::cout << '[' << crate << "] ";
        std::cout << std::endl;
    }
}
