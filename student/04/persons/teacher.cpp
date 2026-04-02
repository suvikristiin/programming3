#include "teacher.hh"


Teacher::Teacher(const std::string &name, int age, const std::string office_num)
    : Person(name, age), office_num_(office_num)
{
    std::cout << "Teacher created: " << name_ << std::endl;
}

Teacher::~Teacher()
{
    std::cout << "Teacher destructed: " << name_ << std::endl;
}

void Teacher::change_room(const std::string &new_room)
{
    office_num_ = new_room;
}

void Teacher::add_new_course(const std::string &course)
{
    courses_.insert(course);
}

void Teacher::remove_course(const std::string &course)
{
    courses_.erase(course);
}

void Teacher::print(std::ostream &output) const
{
    Person::print(output);
    output << "*** " << office_num_ << ": ";

    if (courses_.empty()) {
        output << "No responsibilities";
    } else {
        unsigned int i = 0;
        for (std::string course : courses_) {
            output << course;
            if (i < courses_.size()-1) {
                output << ", ";
            }
            i++;
        }
    }

    output << std::endl;
}




