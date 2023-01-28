#pragma once

#include <iostream>
#include <string>
#include <vector>

static int testNumber = 1;

namespace Ansi
{
static std::string GREEN = "\33[32m";
static std::string RED   = "\33[31m";
static std::string RESET = "\33[39;49m";
} // namespace Ansi

namespace unitTest
{

static void printResult(const bool success)
{
    std::cout << testNumber++ << ')' << " Test";
    std::cout << success ? Ansi::GREEN + " PASSED " : Ansi::RED + " FAILED";
    std::cout << Ansi::RESET << std::endl;
}

static void printResult(const bool success, const std::string &message)
{
    printResult(success);
    std::cout << ": " << message << std::endl;
}

template <typename T>
static void printResult(T actual, T expected, const bool success, const std::string &message)
{
    printResult(success, message);
    if (!success)
        std::cout << "Reason: Expected " << expected << " but was " << actual << std::endl;
}

template <typename T>
static void printResult(T actual, T expected, const bool success)
{
    printResult(success);
    if (!success)
        std::cout << "Reason: Expected " << expected << " but was " << actual << std::endl;
}

inline void assert(const bool expression, const std::string &message)
{
    expression ? printResult(true, message) : printResult(false, message);
}

template <typename T>
void assertEquals(T actual, T expected)
{
    if (actual == expected)
        printResult(true);
    else
        printResult(actual, expected, false);
}

template <typename T>
void assertEquals(T actual, T expected, const std::string &message)
{
    if (actual == expected)
        printResult(true, message);
    else
        printResult(actual, expected, false, message);
}

template <typename T>
void assertEquals(T actual, T expected, const char *message)
{
    assertEquals(actual, expected, std::string(message));
}

template <typename T>
void contains(std::vector<T> &vector, T element, const std::string &message)
{
    if (std::find(vector.begin(), vector.end(), element) != vector.end())
        printResult(true, message);
    else
        printResult(false, message);
}

} // namespace unitTest