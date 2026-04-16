#include "datetime.hh"
#include "dateexception.hh"

using namespace std;

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : Date(year, month, day), hour_(hour), minute_(minute), second_(second)
{

    if (!isLegal()) {
        string message = "Illegal time " + toIsoFormat();
        throw DateException(message.c_str());
    }
}

DateTime::~DateTime()
{

}

string DateTime::toString()
{
    return Date::toString() + " " + toIsoFormat();

}

string DateTime::toIsoFormat() const
{
    string hourZero;
    string minuteZero;
    string secondZero;

    if (hour_ < 10) {
        hourZero = "0";
    }
    if (minute_ < 10) {
        minuteZero = "0";
    }
    if (second_ <10) {
        secondZero = "0";
    }

    string dayIsoFormat = hourZero + to_string(hour_) + "." + minuteZero + to_string(minute_) + "." + secondZero + to_string(second_);
    return dayIsoFormat;;

}


bool DateTime::isLegal() const
{


    if(hour_ < 0 || hour_ > 24) {
        return false;
    }

    if(minute_ < 0 || minute_ > 59) {
        return false;
    }

    if(second_ < 0 || second_ > 59) {
        return false;
    }


    return true;
}
