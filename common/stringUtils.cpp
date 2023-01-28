#include "stringUtils.h"
#include "CustomException.h";

std::ifstream util::readFile(const std::string &fileName)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
        throw FileNotFoundError(fileName);

    return inputFile;
}

std::vector<std::string> util::splitString(const std::string &inputStr, const char delimiter)
{
    std::vector<std::string> stringSplits;
    size_t searchOffset = 0, delimiterPos = 0;

    // Find all delimiter positions and extract each substring between them
    while ((delimiterPos = inputStr.find(delimiter, searchOffset)) != std::string::npos)
    {
        stringSplits.push_back(inputStr.substr(searchOffset, delimiterPos - searchOffset));
        // Set the search offset to after the found delimiter.
        searchOffset = delimiterPos + 1;
    }

    // Extract the last split
    stringSplits.push_back(inputStr.substr(searchOffset));

    return stringSplits;
}

std::vector<std::string> util::splitString(const std::string &inputStr, const std::string &delimiter)
{
    std::vector<std::string> stringSplits;
    size_t searchOffset = 0, delimiterPos = 0;

    // Find all delimiter positions and extract each substring between them
    while ((delimiterPos = inputStr.find(delimiter, searchOffset)) != std::string::npos)
    {
        stringSplits.push_back(inputStr.substr(searchOffset, delimiterPos - searchOffset));
        // Set the search offset to after the found delimiter.
        searchOffset = delimiterPos + delimiter.length();
    }

    // Extract the last split
    stringSplits.push_back(inputStr.substr(searchOffset));

    return stringSplits;
}

void util::resetStream(std::ifstream &stream)
{
    stream.clear();
    stream.seekg(0, std::ios::beg);
}
