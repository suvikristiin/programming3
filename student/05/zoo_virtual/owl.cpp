#include "owl.hh"

Owl::Owl()
{
}

Owl::~Owl()
{
}

void Owl::vocalize(std::ostream &output)
{
    output << "Hoo hoo!" << std::endl;
}
