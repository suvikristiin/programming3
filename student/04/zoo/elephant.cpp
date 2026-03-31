#include "elephant.hh"

Elephant::Elephant():
    Mammal()
{

}

Elephant::~Elephant()
{
}

void Elephant::trumpet(std::ostream &output)
{
    output << "Baraag baraag!" << std::endl;
}
