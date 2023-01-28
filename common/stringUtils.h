#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace util
{

std::ifstream readFile(const std::string &fileName);
std::vector<std::string> splitString(const std::string &inputStr, const char delimiter);
std::vector<std::string> splitString(const std::string &inputStr, const std::string &delimiter);
void resetStream(std::ifstream &stream);

} // namespace util