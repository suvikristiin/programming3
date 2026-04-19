#include "elephant.hh"

Elephant::Elephant():
    Mammal()
{

}

Elephant::~Elephant()
{
}

void Elephant::vocalize(std::ostream &output)
{
    output << "Baraag baraag!" << std::endl;
}
