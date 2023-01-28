#include <stringUtils.h>
#include <unitTests.h>

#include "Day14.h"
#include "Day7.h"

int main()
{
    Day14 day;

    unitTest::assertEquals(day.part1(day.getTestFile()), day.getExpectedValP1());
    // unitTest::assertEquals(day.part2(day.getTestFile()), day.getExpectedValP2());

     std::cout << "Result Part 1: " << day.part1(day.getInputFile()) << std::endl;
    //  std::cout << "Result Part 2: " << day.part2(day.getInputFile()) << std::endl;
}