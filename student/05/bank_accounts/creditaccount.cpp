#include "creditaccount.hh"
#include <iostream>


CreditAccount::CreditAccount(const std::string &owner) : Account(owner), credit_limit_(0)
{}

CreditAccount::~CreditAccount()
{}

bool CreditAccount::take_money(double amount)
{
    if (Account::take_money(amount)){
        return true;
    }
    else if (amount-balance_ <= credit_limit_){
        balance_ = balance_-amount;
        return true;
    }
    else {
        std::cout << "ERROR! Cannot take money: credit limit overflow" << std::endl;
        return false;
    }
}

void CreditAccount::print() const
{
    Account::print();
    std::cout << "  ::: Credit limit : " << credit_limit_ << std::endl;
}

void CreditAccount::set_credit_limit(double limit)
{
    credit_limit_ = limit;
}

double CreditAccount::get_credit_limit() const
{
    return credit_limit_;
}
