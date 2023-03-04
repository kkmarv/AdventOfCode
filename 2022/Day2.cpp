#pragma once

#include "Days.h"

std::string Day2::part1(std::ifstream &inputFile)
{
    util::resetStream(inputFile);

    int score1 = 0;
    int score2 = 0;

    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.empty())
            continue;

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
    return std::to_string(score1) + " " + std::to_string(score2);
}

std::string part2(std::ifstream &inputFile)
{
    return "";
}
