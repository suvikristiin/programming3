/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: card.cpp                                                            #
# Description: Implements Card class functionality.                         #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#include "card.hh"
#include <iostream>

unsigned int Card::NEXT_ID = 1;

Card::Card() :
    ID_(NEXT_ID++)
{

}

Card::~Card()
{

}

bool Card::add_new_definitions(const Fields &field_types,
                               const Fields &definitions)
{

    if (field_types.size() != definitions.size()) {
        return false;
    }

    Fields::const_iterator field_iteration = field_types.begin();
    Fields::const_iterator def_iteration = definitions.begin();

    while (field_iteration != field_types.end()) {
        definitions_[*field_iteration] = *def_iteration;
        ++field_iteration;
        ++def_iteration;
    }

    return true;
}

bool Card::has_fields(const Fields &fields) const
{

}

bool Card::get_definitions(const Fields &requested_fields,
                           Fields &return_definitions)
{

}

double Card::check_answers(const Fields& answer_fields,
                           const Fields& answers) const
{

}

bool Card::print_card(const Fields& print_fields) const
{
    cout << " " << ID_ << " |";
    for (string field : print_fields) {
        map<string, string>::const_iterator it = definitions_.find(field);

        if (it == definitions_.end()) {
            return false;
        }

        cout << " " << it->second << " |";

    }

    cout<<endl;
    return true;
}

bool Card::operator==(const Card &other) const
{
    return ID_ == other.ID_;
}

