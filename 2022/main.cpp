#include <stringUtils.h>
#include <unitTests.h>

#include "Day14.h"
#include "Day7.h"

int main()
{
    Day14 day;

    unitTest::assertEquals(day.part1(day.getTestFile()), day.getExpectedValuePart1());
    std::cout << "Result Part 1:" << std::endl << day.part1(day.getInputFile()) << std::endl;

    // unitTest::assertEquals(day.part2(day.getTestFile()), day.getExpectedValuePart2());
    // std::cout << "Result Part 2: " << std::endl << day.part2(day.getInputFile()) << std::endl;
}