#ifndef CIRCLE_HH
#define CIRCLE_HH
#include "shape.hh"

class Circle : public Shape
{
public:
    Circle(char color, double radius);
    virtual ~Circle();
    virtual double area();
    virtual double circumference();
    virtual void print(int running_number);
private:
    double radius_;
};

#endif // CIRCLE_HH
