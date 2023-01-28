#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace util
{

/**
 * @brief Reads a file and returns its contents.
 * @param path The path to a file.
 * @return An ifstream containing the file content.
 * @throws FileNotFoundError if path does not point to a file.
 */
std::ifstream readFile(const std::string &path);

/**
 * @brief Split a string on a given delimiter.
 * @param inputStr The string which to split.
 * @param delimiter The character on which to split the string.
 * @return
 */
std::vector<std::string> splitString(const std::string &inputStr, const char delimiter);

/**
 * @brief Split a string on a given delimiter.
 * @param inputStr The string which to split.
 * @param delimiter The string sequence on which to split the string.
 * @return
 */
std::vector<std::string> splitString(const std::string &inputStr, const std::string &delimiter);

/**
 * @brief Call clear on a stream and reset the cursor to position 0.
 * @param stream The stream.
 */
void resetStream(std::ifstream &stream);

} // namespace util