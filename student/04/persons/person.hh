#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <iostream>

class Person
{
public:
    // Constructor
    Person(const std::string& name, int age);

    // Destructor
    virtual ~Person();

    // Returns person's name
    std::string get_name() const;

    // Updates person's age as the given parameter
    virtual void celebrate_birthday(int next_age);

    // Prints person's data in the format: <name> : <age>
    virtual void print(std::ostream& output) const;

protected:
    std::string name_;
    int age_;
};

#endif // PERSON_HH
