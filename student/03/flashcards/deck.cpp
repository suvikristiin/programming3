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
# - Name: Suvi Vehmaanperä
# - Student number: 151335682
# - Gitlab user name: xgsuve
# - Tuni email: suvi.vehmaanpera@tuni.fi                                                                      #
#############################################################################
*/

#include "deck.hh"

#include <iostream>
#include <algorithm>

using namespace std;
const string& ERROR_FIELDS = "Error: Incorrect field information.";

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

vector<unsigned int> Deck::get_card_ids()
{
    vector<unsigned int> ids;

    for(const shared_ptr<Card>& c : cards_) {

        if(c) ids.push_back(c->get_id());
    }

    return ids;
}

bool Deck::add_card(shared_ptr<Card> card)
{
    for (const shared_ptr<Card>& c : cards_) {

        if (*c == *card) {
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
    if (cards_studied >= cards_.size()) {
        return nullptr;
    }

    return cards_.at(cards_studied);
}

bool Deck::has_fields(const Fields &fields) {

    for (const string& field : fields) {

        if (find(deck_fields_->begin(), deck_fields_->end(), field) == deck_fields_->end()) {
            return false;
        }
    }

    return true;
}

bool Deck::print_deck(const Fields &requested_fields)
{

    if (!has_fields(requested_fields)){
        cout << ERROR_FIELDS << endl;
        return false;
    }

    cout << name_ << " (" << get_deck_size() << " cards)" << endl;
    cout << endl << "   |";

    for (const string& field : requested_fields) {
        cout << " " << field << " |";
    }

    cout << endl;

    for (const shared_ptr<Card>& card : cards_) {
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


