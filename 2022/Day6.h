#pragma once

#include <fstream>
#include <unordered_map>

#include <stringUtils.h>

#include "DayTemplate.h"

class Day6 : public DayTemplate<std::vector<std::string>>
{
  public:
    Day6() : DayTemplate("7 5 6 10 11 ", "19 23 23 29 26 ", "day6_input.txt", "day6_test.txt") {}

    std::string part1(std::ifstream &inputFile) override
    {
        auto messages = parseInputFile(inputFile);

        std::string resultString = "";
        for (const std::string &message : messages)
            resultString += do_it(message) + " ";

        return resultString;
    }

    std::string part2(std::ifstream &inputFile) override
    {
        auto messages = parseInputFile(inputFile);

        std::string resultString = "";
        for (const std::string &message : messages)
            resultString += do_it(message, 14) + " ";

        return resultString;
    }

  private:
    std::vector<std::string> parseInputFile(std::ifstream &inputFile) override
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
    std::string do_it(const std::string &message, const int window_size = 4) const
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
                const char pebbles = message[i - window_size];

                --charCount[pebbles];
                if (charCount[pebbles] == 0)
                    charCount.erase(pebbles);
            }

            // we have what we searched for when there are 4 chars of count 1
            if (charCount.size() == window_size)
                break;
        }

        return std::to_string(i + 1);
    }
};