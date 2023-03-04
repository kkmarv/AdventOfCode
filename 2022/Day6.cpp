#include "Days.h"

std::string Day6::part1(std::ifstream &inputFile)
{
    auto messages = parseInputFile(inputFile);

    std::string resultString = "";
    for (const std::string &message : messages)
        resultString += findMessageStart(message) + " ";

    return resultString;
}

std::string Day6::part2(std::ifstream &inputFile)
{
    auto messages = parseInputFile(inputFile);

    std::string resultString = "";
    for (const std::string &message : messages)
        resultString += findMessageStart(message, 14) + " ";

    return resultString;
}

std::vector<std::string> Day6::parseInputFile(std::ifstream &inputFile)
{
    std::vector<std::string> messages;

    util::resetStream(inputFile);
    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

        messages.push_back(line);
    }

    return messages;
}

/**
 * @brief Returns the first index of a packet in a given datastream.
 * The start of a packet is defined by the first non-repeating sequence of characters occurring in a datastream.
 * @param message
 * @param window_size
 * @return
 */
std::string Day6::findMessageStart(const std::string &message, const int window_size = 4) const
{
    std::unordered_map<char, int> charCount;

    if (message.length() <= 4)
        return "";

    int i = 0;
    for (; i < message.length(); ++i)
    {
        ++charCount[message[i]];

        // remove chars that fall out off the window
        if (i >= window_size)
        {
            const char charIdxToRemove = message[i - window_size];

            --charCount[charIdxToRemove];
            if (charCount[charIdxToRemove] == 0)
                charCount.erase(charIdxToRemove);
        }

        // we have what we searched for when there are 4 chars of count 1
        if (charCount.size() == window_size)
            break;
    }
    return std::to_string(i + 1);
}