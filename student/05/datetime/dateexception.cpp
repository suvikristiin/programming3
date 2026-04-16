#include "dateexception.hh"


DateException::DateException(const char *message)
    : domain_error(message)
{

}

DateException::~DateException()
{

}
