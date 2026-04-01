#include "rockpaperscissors.hh"
#include <iostream>

RockPaperScissors::RockPaperScissors(unsigned int rounds)
: BaseGame(rounds)
{

}

RockPaperScissors::~RockPaperScissors()
{
}

void RockPaperScissors::printGameName() const
{
    std::cout << "Rock-Paper-Scissors Game" << std::endl;
}

unsigned int RockPaperScissors::roundWinner(const std::string &word1, const std::string &word2) const
{
    if (word1 == word2) {
        return 0;
    }

    if(word1 == "rock") {
        if (word2 == "paper") {
            return 2;
        } else {
            return 1;
        }
    } else if (word1 == "paper") {
        if (word2 == "scissors") {
            return 2;
        } else {
            return 1;
        }
    } else if(word1 == "scissors") {
        if (word2 == "rock") {
            return 2;
        } else {
            return 1;
        }
    } else {
        if (word2 == "rock" || word2 == "scissors" || word2 == "paper")  {
            return 2;
        } else {
            return 0;
        }
    }
}
