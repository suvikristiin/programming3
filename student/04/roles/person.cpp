#include "person.hh"
#include "role.hh"
#include <iostream>

Person::Person(const std::string &name)
    : name_(name)
{
    std::vector<Role*> roles_;
}


Person::~Person()
{

}

void Person::add_role(Role *role)
{
    roles_.push_back(role);
}



void Person::print(std::ostream &output) const
{
    if (roles_.empty()) {
        output << "No roles" <<std::endl;
    } else {
        for (Role* role : roles_) {
            output << "Role started at ";
            role->print(output);
        }

    }
}

void Person::print_name(std::ostream &output) const
{
    output << name_ << std::endl;
}

