#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include <stringUtils.h>

#include "DayTemplate.h"

class Day2 : public DayTemplate
{
  private:
    std::ifstream inputFile         = util::readFile("./day2_input.txt");
    std::ifstream testFile          = util::readFile("./day2_test.txt");
    const std::string expectedValP1 = "";
    const std::string expectedValP2 = "";

    static enum Move
    {
        ROCK     = 1,
        PAPER    = 2,
        SCISSORS = 3
    };
    static enum Outcome
    {
        LOSE = 0,
        DRAW = 3,
        WIN  = 6
    };

  public:
    std::string part1(std::ifstream &inputFile) override
    {
        util::resetStream(inputFile);

        int score1 = 0, score2 = 0;

        for (std::string line; std::getline(inputFile, line);)
        {
            if (line.empty())
            {
                continue;
            }

            char lMove = line[0];
            char rMove = line[line.size() - 1];

            // Left plays Rock
            if (lMove == 'A')
            {
                switch (rMove)
                {
                case 'X':
                    score1 += Move::ROCK + Outcome::DRAW;
                    score2 += Outcome::LOSE + Move::SCISSORS;
                    break;
                case 'Y':
                    score1 += Move::PAPER + Outcome::WIN;
                    score2 += Outcome::DRAW + Move::ROCK;
                    break;
                case 'Z':
                    score1 += Move::SCISSORS + Outcome::LOSE;
                    score2 += Outcome::WIN + Move::PAPER;
                    break;
                default:
                    break;
                }
            }
            // Left plays Paper
            else if (lMove == 'B')
            {
                switch (rMove)
                {
                case 'X':
                    score1 += Move::ROCK + Outcome::LOSE;
                    score2 += Outcome::LOSE + Move::ROCK;
                    break;
                case 'Y':
                    score1 += Move::PAPER + Outcome::DRAW;
                    score2 += Outcome::DRAW + Move::PAPER;
                    break;
                case 'Z':
                    score1 += Move::SCISSORS + Outcome::WIN;
                    score2 += Outcome::WIN + Move::SCISSORS;
                    break;
                default:
                    break;
                }
            }
            // Left plays Scissors
            else
            {
                switch (rMove)
                {
                case 'X':
                    score1 += Move::ROCK + Outcome::WIN;
                    score2 += Outcome::LOSE + Move::PAPER;
                    break;
                case 'Y':
                    score1 += Move::PAPER + Outcome::LOSE;
                    score2 += Outcome::DRAW + Move::SCISSORS;
                    break;
                case 'Z':
                    score1 += Move::SCISSORS + Outcome::DRAW;
                    score2 += Outcome::WIN + Move::ROCK;
                    break;
                default:
                    break;
                }
            }
        }

        std::cout << score1 << std::endl;
        std::cout << score2;
    }
};
