#include "programmer.hh"


Programmer::Programmer(int from_year)
    : Role(from_year)
{
    std::set<std::string> skills_;
}

Programmer::~Programmer()
{

}

void Programmer::add_skill(const std::string &skill)
{
    skills_.insert(skill);
}

void Programmer::print(std::ostream &output) const
{
    if (skills_.empty()) {
        output << "No skills" <<std::endl;
    } else {
        output << "Skills: ";
        unsigned int i = 0;
        for (const std::string& skill : skills_) {
            output << skill;
            if (i+1 < skills_.size()) {
                output << " ";
            }
            i++;
        }

    }
    output <<std::endl;
}
