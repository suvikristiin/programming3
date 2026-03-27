/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukortit / Flashcards                                      #
#############################################################################
*
* Description:
* The program allows the user to create and manage decks consisting of cards.
* Each card contains field–definition pairs (fields and their corresponding definitions), which can be used for studying.
* The program uses a command-line interface (CLI) for user interaction.
*
* Main functionalities:
* - Creating new decks with user-defined fields
* - Adding cards with definitions to decks
* - Reading decks and cards from a file
* - Printing deck contents
* - Copying cards between decks
* - Studying cards and checking answers
* - Calculating a score based on correct answers
*
* Author information
* - Name: Suvi Vehmaanperä
* - Student number: 151335682
* - Gitlab user name: xgsuve
* - Tuni email: suvi.vehmaanpera@tuni.fi
*
* Notes on the implementation choices:
* - Smart pointers (shared_ptr) are used for dynamic memory management
* - Each Card is assigned a unique ID to distinguish cards and support comparisons.
*
* Documentation of the use of AI tools (tool name and application):
 * OpenAI ChatGPT version 5.3 was used during the development process as a supporting tool for:
 * - identifying and fixing errors in the code
 * - clarifying programming concepts
*/

#include "cli.hh"

#include <iostream>

using namespace std;

int main()
{
    cout << "[Flashcards]" << endl << endl;

    shared_ptr<Cli> cli = make_shared<Cli>();
    if ( not cli->run_program() )
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
