#ifndef RECTANGLE_HH
#define RECTANGLE_HH
#include "shape.hh"

class Rectangle : public Shape
{
public:
    Rectangle(char color, double width, double height);
    virtual ~Rectangle();
    virtual double area();
    virtual double circumference();
    virtual void print(int running_number);
private:
    double width_;
    double height_;
};

#endif // RECTANGLE_HH
