#include "timedepositaccount.hh"
#include <iostream>


TimeDepositAccount::TimeDepositAccount(const std::string &owner) : Account(owner), time_(0)
{}

TimeDepositAccount::~TimeDepositAccount()
{}

bool TimeDepositAccount::take_money(double amount)
{
    if (time_ <= 0){
        return Account::take_money(amount);
    }
    else {
        std::cout << "ERROR! Cannot take money: deposit time has not expired" << std::endl;
        return false;
    }
}

void TimeDepositAccount::print() const
{
    Account::print();
    std::cout << "  ::: Days left : " << time_ << std::endl;
}

void TimeDepositAccount::set_times(int time)
{
    time_ = time*365;
}

void TimeDepositAccount::spend_time(int time)
{
    time_ -= time;
}

int TimeDepositAccount::get_time_limit()
{
    return time_;
}
