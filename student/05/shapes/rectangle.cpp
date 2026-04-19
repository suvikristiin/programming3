#include "rectangle.hh"
#include <iostream>

Rectangle::Rectangle(char color, double width, double height)
    : Shape(color), width_(width), height_(height)
{

}

Rectangle::~Rectangle()
{

}

double Rectangle::area()
{
    double area = width_ * height_;

    return area;
}

double Rectangle::circumference()
{
    double circum = 2 * width_ + 2 * height_;

    return circum;
}

void Rectangle::print(int running_number)
{
    Shape::print(running_number);


    cout << COLOR_NAMES.at(get_color()) << " rectangle with width " << width_  << " and height " << height_ << endl;
    cout << "Area: " << area() <<endl;
    cout << "Circumference: " << circumference() <<endl;
}




