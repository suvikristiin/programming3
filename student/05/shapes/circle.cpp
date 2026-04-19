#include "circle.hh"
#include <iostream>

Circle::Circle(char color, double radius)
    : Shape(color), radius_(radius)
{

}

Circle::~Circle()
{

}

double Circle::area()
{
    double area = 3.14159 * radius_ * radius_;

    return area;
}

double Circle::circumference()
{
    double circum = 2 * 3.14159 * radius_;

    return circum;
}

void Circle::print(int running_number)
{
    Shape::print(running_number);

    cout << COLOR_NAMES.at(get_color()) << " circle with radius " << radius_ << endl;
    cout << "Area: " << area() <<endl;
    cout << "Circumference: " << circumference() <<endl;
}
