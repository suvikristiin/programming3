#include "date.hh"

//TODO: Implement other functions here

using namespace std;


Date::Date(int year, int month, int day) :
    year_(year), month_(month), day_(day)
{

}

Date::~Date()
{

}

int Date::getYear() const
{
    return year_;;
}

int Date::getMonth() const
{
    return month_;
}

int Date::getDay() const
{
    return day_;
}

string Date::toString() const
{
    string dayString = to_string(day_) + "."  + to_string(month_) + "." + to_string(year_);
    return dayString;;
}

std::string Date::toIsoFormat() const
{
    string monthZero;
    string dayZero;

    if (day_ < 10) {
        dayZero = "0";
    }
    if (month_ < 10) {
        monthZero = "0";
    }

    string dayIsoFormat = to_string(year_) + "-"  + monthZero + to_string(month_) + "-" + dayZero + to_string(day_);
    return dayIsoFormat;;

    return"";
}

bool Date::isLeapYear() const
{
    return (year_ % 4 == 0) and ((year_ % 100 != 0) or (year_ % 400 == 0));
}

bool Date::isLegal() const
{


    if(year_ < 1000 || year_ > 9999) {
        return false;
    }

    if(month_ < 1 || month_ > 12) {
        return false;
    }

    if(day_ < 1) {
        return false;
    }

    // 4. Karkausvuosi?
    bool leap = isLeapYear();

    int days_in_month;

    if(month_ == 2) {
        days_in_month = leap ? 29 : 28;
    }
    else if(month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) {
        days_in_month = 30;
    }
    else {
        days_in_month = 31;
    }

    // 6. Lopullinen tarkistus
    if(day_ > days_in_month) {
        return false;
    }

    return true;
}

bool Date::operator<(const Date& other) const
{
    if(year_ != other.year_) {
        return year_ < other.year_;
    }
    if(month_ != other.month_) {
        return month_ < other.month_;
    }
    return day_ < other.day_;
}

bool Date::operator==(const Date& other) const
{
    if(year_ == other.year_) {
        return year_ == other.year_;
    }
    if(month_ == other.month_) {
        return month_ == other.month_;
    }
    if(day_ == other.day_) {
        return day_ == other.day_;
    }
    return day_ !=  other.day_;
}

