/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deck.cpp                                                            #
# Description: Implements the Deck class functionality.                     #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
#                                                                           #
#############################################################################
*/

#include "deck.hh"

#include <iostream>

using namespace std;

const string NO_CARDS = "No cards have been added.";

Deck::Deck(string deck_name, const Fields& fields) :
    name_(deck_name), deck_fields_(make_shared<Fields>(fields))
{

}

Deck::~Deck()
{

}

bool Deck::add_card(const Fields &card_fields, const Fields &definitions)
{
    shared_ptr<Card> new_card = make_shared<Card>();

    if (!new_card->add_new_definitions(card_fields, definitions)) {
        return false;
    }

    cards_.push_back(new_card);
    return true;
}

bool Deck::add_card(shared_ptr<Card> card)
{
    for (const shared_ptr<Card>& c : cards_) {
        if (*c == *card) {  // sama ID
            return false;
        }
    }

    cards_.push_back(card);
    return true;
}

bool Deck::copy_cards(shared_ptr<Deck> destination)
{
    shared_ptr<Fields> dest_fields = destination->get_fields();

    for (const shared_ptr<Card>& card : cards_) {

        if (!card->has_fields(*dest_fields)) {
            continue;
        }

        destination->add_card(card);
    }

    return true;
}

shared_ptr<Card> Deck::get_next_study_card(unsigned int& cards_studied)
{

}

bool Deck::print_deck(const Fields &requested_fields)
{

    for (const string& field : requested_fields) {
        if (find(deck_fields_->begin(), deck_fields_->end(), field) == deck_fields_->end()) {
            cout << "Error: Incorrect field information." << endl;
            return false;
        }
    }


    cout << name_ << " (" << get_deck_size() << " cards)" << endl;
    cout << endl << "   |";

    for (const string& field : requested_fields) {
        cout << " " << field << " |";
    }
    cout << endl;

    for (shared_ptr<Card> card : cards_) {
        card->print_card(requested_fields);
    }

    return true;
}

shared_ptr<Fields> Deck::get_fields()
{
    return deck_fields_;
}

size_t Deck::get_deck_size()
{
    return cards_.size();
}


