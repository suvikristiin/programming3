#include "servicedata.hh"
#include <map>
#include <iostream>

using namespace std;

ServiceData::ServiceData()
{
    map<int, Service> services_;
}

ServiceData::~ServiceData()
{

}

bool ServiceData::makeService(const Service &service, int kilometres)
{

    for ( pair<int, Service> tietopari : services_ ) {
        if ( tietopari.first == kilometres ) {
            cout <<"Error: already serviced with the same kilometres" << endl;
            return false;
        }
    }

    services_.insert( { kilometres, service } );

    return true;
}

void ServiceData::print() const
{

    for ( pair<int, Service> tietopari : services_ ) {
        cout << "* Kilometres driven " << tietopari.first << " until " << tietopari.second.date_ << endl;

        for (string operation : tietopari.second.operations_) {
            cout << "  --- " << operation << endl;
        }
    }
}

const std::map<int, Service> &ServiceData::getServices() const
{
    return services_;
}


