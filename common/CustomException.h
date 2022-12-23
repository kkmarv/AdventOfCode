#pragma once

#include <stdexcept>


class FileNotFoundError : public std::runtime_error {
 public:
  FileNotFoundError(const std::string& fileName) : std::runtime_error(_message + fileName) {
    std::cout << this->what() << std::endl;
  }

 private:
  inline static const std::string _message = "File not found: ";
};
