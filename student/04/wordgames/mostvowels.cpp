#include "mostvowels.hh"
#include <iostream>

MostVowels::MostVowels(unsigned int rounds)
    : BaseGame(rounds)
{}

MostVowels::~MostVowels()
{

}

void MostVowels::printGameName() const
{
    std::cout << "Most Vowels Game" << std::endl;

}

unsigned int MostVowels::roundWinner(const std::string &word1, const std::string &word2) const
{
    int countWord1 = 0;
    int countWord2 = 0;

    for (char c : word1) {
        c = std::tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            countWord1++;
        }
    }

    for (char c : word2) {
        c = std::tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            countWord2++;
        }
    }

    if(countWord1 > countWord2)
    {
        return 1;
    }
    else if(countWord1 < countWord2)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}





