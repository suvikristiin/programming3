#ifndef DATE_HH
#define DATE_HH
#include <string>

using namespace std;

// Some bound values
const int FIRST_DAY = 1;
const int FIRST_MONTH = 1;
const int FIRST_YEAR = 1000;
const int LAST_YEAR = 9999;

// Number of days in months
int const MONTH_SIZES[12] = { 31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31 };


class Date
{
public:
    Date(int year, int month, int day);
    virtual ~Date();

    int getYear();
    int getMonth();
    int getDay();
    virtual string toString();

private:
    bool isLegal() const;
    bool isLeapYear() const;
    string toIsoFormat() const;
protected:
    int year_;
    int month_;
    int day_;
};

#endif // DATE_HH
