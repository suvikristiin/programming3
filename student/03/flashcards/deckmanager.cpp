/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
# File: deckmanager.cpp                                                     #
# Description: Implements DeckManager functionality.                        #
#                                                                           #
# Notes:                                                                    #
#                                                                           #
# Author information:                                                       #
* - Name: Suvi Vehmaanperä
* - Student number: 151335682
* - Gitlab user name: xgsuve
* - Tuni email: suvi.vehmaanpera@tuni.fi                                                                      #
#############################################################################
*/

#include "deckmanager.hh"
#include "utils.hh"

#include <iostream>
#include <iomanip>

using namespace std;

const string& PROMPT_FIELDS_PRINT = "Choose fields to print: ";
const string& PROMPT_FIELDS_ANSWER = "Choose fields to answer: ";
const string& PROMPT_TYPE_FIELDS = "Type all fields separated with spaces: ";
const string& PROMPT_TYPE_DEFINITIONS = "Type all definitions line by line: ";

const string& NO_DECKS = "No decks have been added.";
const string& NO_CARDS = "No cards have been added.";

const string& MESSAGE_STUDY_PROMPTS = "Prompts shown in: ";
const string& MESSAGE_STUDY_ANSWERS = "Type answers in: ";
const string& MESSAGE_STUDY_RESULT = "Final result of the study session: ";

const string& FIELDS_PROMPT = "FIELDS> ";

DeckManager::DeckManager() {}

DeckManager::~DeckManager() {}

void DeckManager::print_decks() const
{
    if (decks_.empty()) {
        cout << NO_DECKS <<endl;
        return;
    }

    for (const pair<const string, shared_ptr<Deck>>& deck : decks_) {
        cout << "- " << deck.first << " (" << deck.second->get_deck_size() << " cards)" << endl;
    }

}

shared_ptr<Deck> DeckManager::add_deck(string deck_name)
{
    vector<string> input_fields;
    cout << PROMPT_TYPE_FIELDS << endl;
    cout << FIELDS_PROMPT;
    string input = "";
    getline(cin, input);
    input_fields = split(input, ' ');
    shared_ptr<Deck> new_deck =  make_shared<Deck>(deck_name, input_fields);
    decks_[deck_name] = new_deck;

    return new_deck;
}

shared_ptr<Deck> DeckManager::add_deck(string deck_name,
                                       const Fields &field_types)
{
    if (decks_.find(deck_name) != decks_.end()) {
        return nullptr;
    }

    shared_ptr<Deck> new_deck =  make_shared<Deck>(deck_name, field_types);
    decks_.insert({deck_name, new_deck});

    return new_deck;
}

bool DeckManager::add_card(string deck_name)
{

    map<string, shared_ptr<Deck>>::iterator it = decks_.find(deck_name);

    if (it == decks_.end()) {
        return false;
    }

    shared_ptr<Deck> deck = it->second;
    shared_ptr<Fields> deck_fields = deck->get_fields();
    cout << PROMPT_TYPE_DEFINITIONS << endl;
    vector<string> input_fields;
    string input;

    for (const string& field : *deck_fields) {
        cout << field << ": ";
        getline(cin, input);
        input_fields.push_back(input);
    }

    cout << endl;

    return deck->add_card(*deck_fields, input_fields);
}

void DeckManager::overview(const string& deck_name)
{

    map<string, shared_ptr<Deck>>::iterator it = decks_.find(deck_name);
    shared_ptr<Deck> deck = it->second;
    const size_t& EMPTY_DECK = 0;

    if (deck->get_deck_size() == EMPTY_DECK) {
        cout << NO_CARDS <<endl;
        return;
    }

    Fields input_fields;
    bool allow_all = true;
    ask_fields(deck_name, PROMPT_FIELDS_PRINT, input_fields, allow_all);
    deck->print_deck(input_fields);
}

bool DeckManager::copy(string source_deck_name,
                       string destination_deck_name)
{
    map<string, shared_ptr<Deck>>::const_iterator source_it = decks_.find(source_deck_name);
    map<string, shared_ptr<Deck>>::const_iterator dest_it = decks_.find(destination_deck_name);

    if (source_it == decks_.end()) return false;

    if (dest_it == decks_.end()) {
        shared_ptr<Deck> new_destination_deck =  make_shared<Deck>(destination_deck_name, *source_it->second->get_fields());
        decks_[destination_deck_name] = new_destination_deck;
        dest_it = decks_.find(destination_deck_name);
    }

    if (!fields_match(*source_it->second->get_fields(), *dest_it->second->get_fields())) {
        return false;
    }

    if(!source_it->second->copy_cards(dest_it->second)) {
        return false;
    }

    return true;
}

bool DeckManager::run_study(const string &deck_name)
{
    map<string, shared_ptr<Deck>>::iterator it = decks_.find(deck_name);
    shared_ptr<Deck> deck = it->second;
    const size_t& EMPTY_DECK = 0;

    if (deck->get_deck_size() == EMPTY_DECK) {
        cout << NO_CARDS <<endl;
        return false;
    }

    Fields prompt_fields;
    Fields answers_fields;
     bool allow_all = false;
    ask_fields(deck_name, PROMPT_FIELDS_PRINT, prompt_fields, allow_all);
    ask_fields(deck_name, PROMPT_FIELDS_ANSWER, answers_fields, allow_all);
    shared_ptr<Fields> fields = deck->get_fields();

    if (!deck->has_fields(prompt_fields) || !deck->has_fields(answers_fields)){
        return false;
    }

    cout << "Study " << deck->get_deck_size() << " cards" <<endl;
    cout << MESSAGE_STUDY_PROMPTS;

    for (const string& prompt_field : prompt_fields) {
        cout << prompt_field << " ";
    }

    cout <<endl;
    cout << MESSAGE_STUDY_ANSWERS;

    for (const string& answer_field : answers_fields) {
        cout << answer_field << " ";
    }

    double total_points = 0.0;
    unsigned int cards_studied = 0;
    cout <<endl;
    cout <<endl;

    while (true) {
        shared_ptr<Card> card = deck->get_next_study_card(cards_studied);

        if (card == nullptr) {
            break;
        }

        Fields question_fields;
        card->get_definitions(prompt_fields, question_fields);
        unsigned int i = 0;

        while (i < question_fields.size()) {
            cout << question_fields.at(i);

            if (i != question_fields.size() - 1) {
                cout << "/";
            }
            i++;
        }

        cout << ": ";
        string input_answers;
        getline(cin, input_answers);
        Fields user_answers = split(input_answers, ' ');
        total_points += card->check_answers(answers_fields, user_answers);
        cards_studied++;

    }

    cout <<endl;
    double result = (total_points/static_cast<double>(cards_studied)) * 100;
    cout << MESSAGE_STUDY_RESULT << fixed << setprecision(2) << result << "%" << endl;

    return true;
}

bool DeckManager::deck_exists(const string &deck_name) const
{

    if (decks_.find(deck_name) != decks_.end()) {
        return true;
    }

    return false;
}

shared_ptr<Fields> DeckManager::get_deck_fields(const string &deck_name) const
{
    map<string, shared_ptr<Deck>>::const_iterator it = decks_.find(deck_name);

    if (it == decks_.end()) {
        return nullptr;
    }

    return it->second->get_fields();
}

void DeckManager::ask_fields(const string& deck_name,
                             const string& prompt_message,
                             Fields& input_fields,
                             bool allow_all) const
{
    if (not deck_exists(deck_name)) {
        return;
    }

    shared_ptr<Fields> deck_fields = get_deck_fields(deck_name);
    cout << prompt_message << endl;

    for (const string& field : *deck_fields) {
        cout << field << " ";
    }

    if (allow_all) {
        cout << "or all";
    }

    cout << endl << FIELDS_PROMPT;
    string input = "";
    getline(cin, input);
    cout << endl;
    input_fields = split(input, ' ');

    if (allow_all and input_fields.size() == 1 and input_fields.at(0) == "all")
    {
        input_fields = *deck_fields;
    }
}

