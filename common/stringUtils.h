#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace util {

   std::ifstream readFile(const std::string& fileName);
   std::vector<std::string> splitString(const std::string& str, char delimiter);
   void resetStream(std::ifstream& stream);

}