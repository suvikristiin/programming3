#ifndef DATEEXCEPTION_HH
#define DATEEXCEPTION_HH
#include <stdexcept>

using namespace std;

class DateException  : public domain_error
{
public:
    DateException(const char* message);

    virtual ~DateException();
};

#endif // DATEEXCEPTION_HH
