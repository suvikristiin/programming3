#include "dateperiod.hh"


DatePeriod::DatePeriod(const Date &d1, const Date &d2) :
    startDate_(d1), endDate_(d2)
{

}

DatePeriod::~DatePeriod()
{

}

string DatePeriod::getStart() const
{
    return startDate_.toIsoFormat();
}

string DatePeriod::getEnd() const
{
    return endDate_.toIsoFormat();
}



unsigned int daysInMonth(unsigned int month, unsigned int year)
{
    if(month == 2) {
        if(Date(year, 1, 1).isLeapYear()) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

unsigned int daysFromFirstDate(const Date& date)
{
    unsigned int days = 0;

    for(unsigned int year = FIRST_YEAR; year < date.getYear(); ++year) {
        if(Date(year, 1, 1).isLeapYear()) {
            days += 366;
        }
        else {
            days += 365;
        }
    }

    for(unsigned int month = 1; month < date.getMonth(); ++month) {
        days += daysInMonth(month, date.getYear());
    }

    days += date.getDay() - 1;

    return days;
}

unsigned int DatePeriod::getDiff() const
{
    unsigned int diffStart = daysFromFirstDate(startDate_);
    unsigned int diffEnd = daysFromFirstDate(endDate_);

    return diffEnd - diffStart;
}
