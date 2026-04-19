#ifndef ANIMAL_HH
#define ANIMAL_HH

#include <iostream>
#include <string>

class Animal
{
public:
    Animal();
    Animal(const std::string& moving_noise);
    virtual ~Animal();
    void move(int x, int y, std::ostream& output);
    void print_location(std::ostream& output) const;
    virtual void vocalize(std::ostream &output) = 0;
private:
    int x_;
    int y_;
    std::string moving_noise_;
};

#endif // ANIMAL_HH
