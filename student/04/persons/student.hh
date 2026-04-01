#include <vector>
#ifndef STUDENT_HH
#define STUDENT_HH
#include "person.hh"


class Student : public Person
{
public:
    Student(const std::string& name, int age, const std::string student_num);
    virtual ~Student();
    void print(std::ostream& output) const override;
    void complete_course(const std::string& course);
private:
    std::string student_num_;
    std::vector<std::string> courses_;
};

#endif // STUDENT_HH
