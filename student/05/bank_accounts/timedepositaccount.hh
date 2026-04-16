#ifndef TIMEDEPOSITACCOUNT_HH
#define TIMEDEPOSITACCOUNT_HH

#include "account.hh"

class TimeDepositAccount : public Account
{
public:
    // Constructor
    TimeDepositAccount(const std::string& owner);

    // Virtual destructor
    virtual ~TimeDepositAccount();

    bool virtual take_money(double amount);

    // Prints all data about the account.
    void virtual print() const;

    // Sets the time limit.
    void set_times(int time);

    void spend_time(int time);

    int get_time_limit();

private:
    int time_;
};

#endif // TIMEDEPOSITACCOUNT_HH
