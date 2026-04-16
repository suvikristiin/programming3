#include "date.hh"
#include "dateexception.hh"


using namespace std;


Date::Date(int year, int month, int day) :
    year_(year), month_(month), day_(day)
{
    if (!isLegal()) {
        string message = "Illegal date " + toIsoFormat();
        throw DateException(message.c_str());
    }
}

Date::~Date()
{

}

int Date::getYear()
{
    return year_;;
}

int Date::getMonth()
{
    return month_;
}

int Date::getDay()
{
    return day_;
}

string Date::toString()
{
    return toIsoFormat();
}

string Date::toIsoFormat() const
{
    string monthZero;
    string dayZero;

    if (day_ < 10) {
        dayZero = "0";
    }
    if (month_ < 10) {
        monthZero = "0";
    }

    string dayIsoFormat = dayZero  + to_string(day_) + "."  + monthZero + to_string(month_) + "." + to_string(year_);
    return dayIsoFormat;

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



