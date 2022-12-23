#include "stringUtils.h"
#include "CustomException.h";


std::ifstream util::readFile(const std::string& fileName) {
  std::ifstream inputFile(fileName);

  if (!inputFile.is_open())
    throw FileNotFoundError(fileName);

  return inputFile;
}

std::vector<std::string> util::splitString(const std::string& str, char delimiter) {
  std::vector<std::string> stringParts;
  size_t searchPos = 0, delimiterPos = 0;

  // Find all delimiter positions and extract each substring between them
  while ((delimiterPos = str.find(delimiter, searchPos)) != std::string::npos) {
    stringParts.push_back(str.substr(searchPos, delimiterPos - searchPos));
    searchPos = delimiterPos + 1;
  }

  // Extract the last split
  stringParts.push_back(str.substr(searchPos));
  return stringParts;
}

void util::resetStream(std::ifstream& stream) {
  stream.clear();
  stream.seekg(0, std::ios::beg);
}
