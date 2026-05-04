/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukorttien paluu / Return of Flashcards                    #
# File: mainwindow.hh                                                       #
# Description: Declares the MainWindow class interface.                     #
#                                                                           #
# Notes: * Implements the GUI of the application.                           #
#        * Acts as a controller between UI and DeckManager, Deck and Card  #
#          via interfaces.                                                 #
#        * Handles user interactions and updates views.                    #
#                                                                           #
# Author information:
# Name: Suvi Vehmaanperä                                                    #
# Student number: 151335682
# Gitlab user name: xgsuve
# Tuni email: suvi.vehmaanpera@tuni.fi
#                                                                         #
#############################################################################
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deckmanager.hh"
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}
/**
 * @brief Application window class.
 *
 * Responsible for:
 * - Handling user interactions (buttons, deck/card clicks)
 * - Displaying decks and cards in the UI
 * - Communicating with DeckManager, Deck and Card class via interfaces.
 * - Updating UI components when data changes
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs MainWindow.
     *
     * Initializes UI and connects signals/slots.
     *
     * @param parent Parent widget (default nullptr)
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Unloads MainWindow and releases UI resources.
     */
    ~MainWindow();

private slots:
    /**
    * @brief Loads decks and its cards from a file.
    */
    void on_loadFileButton_clicked();
    /**
    * @brief Adds a new empty deck based on user input.
    */
    void on_addDeckPushButton_clicked();
    /**
    * @brief Removes the selected deck.
    */
    void on_removeDeckPushButton_clicked();
    /**
    * @brief Removes the selected card from current deck.
    */
    void on_removeCardPushButton_clicked();
    /**
    * @brief Closes the application.
    */
    void on_closePushButton_clicked();
    /**
     * @brief Handles adding a new card from CardWidget.
     * @param definitions User-inputed definitions of the card.
     */
    void add_card(const Fields& definitions);
    /**
     * @brief Handles updating an existing card from CardWidget.
     * @param definitions User-inputed updated definitions of the card.
     */
    void update_card(const Fields& definitions);
    /**
     * @brief Clears the card widget display area.
     */
    void clear_cardWidget_area();

private:
    Ui::MainWindow *ui;
    /// @brief Manages all decks and cards
    shared_ptr<DeckManager> manager_;
     /// @brief Currently selected deck
    shared_ptr<Deck> deck_;
    /// @brief Field types  of current deck
    shared_ptr<Fields> fields_;
    ///@brief Refreshes the list of decks in UI.
    void refresh_deckList();
    /**
     * @brief Handles deck selection from UI list.
     * @param item Selected list widget item.
     */
    void on_deck_clicked(QListWidgetItem* item);
    /**
     * @brief Handles card selection from UI list.
     * @param item Selected list widget item.
     */
    void on_card_clicked(QListWidgetItem* item);
    /**
     * @brief Refreshes the card list for current deck.
     */
    void refresh_cardList();
    /**
     * @brief Sets the card widget to UI in correct mode (view/edit/add UI).
     */
    void set_cardWidget(QWidget* cardWidget);
};

#endif // MAINWINDOW_HH
