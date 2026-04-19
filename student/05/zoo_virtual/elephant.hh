#ifndef ELEPHANT_HH
#define ELEPHANT_HH
#include "mammal.hh"

class Elephant : public Mammal
{
public:
    Elephant();
    virtual ~Elephant();
    //void trumpet(std::ostream& output);
    virtual void vocalize(std::ostream &output);
private:
};

#endif // ELEPHANT_HH
