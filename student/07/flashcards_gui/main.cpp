/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project:  Opettelukorttien paluu / Return of Flashcards                   #
#############################################################################
*
* Description:
* This program is a flashcard application that allows users to
* create, remove and manage decks of study cards.
*
* Each deck contains cards with multiple fields. The application provides a
* graphical user interface for interacting with decks and cards.
*
* The MainWindow acts as the controller between the user interface
* and the underlying data model (DeckManager). It is responsible for
* handling user actions and updating the displayed content.
*
* The project task was to implement a graphical user interface for the given
* Flashcards program. The program code base has already implemented the
* program's operating logic into the DeckManager, Deck and Card classes.
*
* Main functionalities:
* - Load flashcard decks from file
* - Create and delete decks
* - Add, view, edit, and remove cards
* - Display cards dynamically using CardWidget
*
* Author information
* - Name: Suvi Vehmaanperä
* - Student number: 151335682
* - Gitlab user name: xgsuve
* - Tuni email: suvi.vehmaanpera@tuni.fi
*
*/


#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
