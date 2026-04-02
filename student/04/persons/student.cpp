#include "student.hh"


Student::Student(const std::string &name, int age, const std::string student_num) :
    Person(name, age), student_num_(student_num)
{
    std::cout << "Student created: " << name_ << std::endl;
}

Student::~Student()
{
    std::cout << "Student destructed: " << name_ << std::endl;
}

void Student::print(std::ostream &output) const
{
    Person::print(output);

    output << "+++ " << student_num_ << ": ";


    if (courses_.empty()) {
        output << "No courses completed";
    } else {
        unsigned int i = 0;
        for (std::string course : courses_) {
            output << course;
            if (i+1 < courses_.size()) {
                output << ", ";
            }
            i++;
        }
    }

    output << std::endl;
}

void Student::complete_course(const std::string &course)
{
    courses_.push_back(course);
}
