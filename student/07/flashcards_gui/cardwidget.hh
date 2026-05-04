/*
#############################################################################
# COMP.CS.115 Ohjelmointi 3: Rajapinnat / Programming 3: Interfaces         #
# Project: Opettelukorttien paluu / Return of Flashcards                    #
# File: cardwidget.hh                                                       #
# Description: Declares the CardWidget class interface.                     #
#                                                                           #
# Notes: * Provides a UI widget for viewing, editing and adding card.  #
#        * Dynamically builds its interface based on current mode.         #
#        * Emits signals to notify MainWindow about user actions.          #
#                                                                           #
# Author information:
# Name: Suvi Vehmaanperä                                                    #
# Student number: 151335682
# Gitlab user name: xgsuve
# Tuni email: suvi.vehmaanpera@tuni.fi
#                                                                           #
#############################################################################
*/

#ifndef CARDWIDGET_HH
#define CARDWIDGET_HH
#include "card.hh"
#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>

using namespace std;

/**
 * @brief Widget for displaying, adding and editing a flashcard.
 *  Inherits from QWidget and acts as a custom UI component
 *
 * CardWidget supports three modes:
 * - VIEW: shows card content
 * - EDIT: allows modifying existing card
 * - ADD: allows creating a new card
 *
 * The widget communicates with MainWindow via signals.
 */

class CardWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Defines the current UI mode of CardWidget.
     */
    enum Mode {
        VIEW,
        EDIT,
        ADD
    };
    /**
     * @brief Constructs a CardWidget.
     *
     * @param card Shared pointer to the card (nullptr in ADD mode)
     * @param fields Field types of the deck
     * @param mode Initial UI mode (VIEW, EDIT, ADD)
     * @param parent Parent widget (default nullptr)
     */
    CardWidget(shared_ptr<Card> card,
               shared_ptr<Fields> fields,
               Mode mode,
               QWidget* parent = nullptr);
    /**
     * @brief Unloads CardWidget and releases UI resources.
     */
    ~CardWidget();
signals:
    /**
     * @brief Emitted when a new card to be added.
     *
     * @param values User-entered field values for the new card.
     */
    void add_card_requested(const Fields& values);
    /**
     * @brief Emitted when an existing card is updated.
     *
     * @param values Updated field values.
     */
    void card_updated(const Fields& values);

private slots:
    /**
     * @brief Saves edited card data and emits update signal.
     */
    void on_save_clicked();
    /**
     * @brief Switches widget into edit mode.
     */
    void on_edit_clicked();
    /**
     * @brief Emits signal to add a new card.
     */
    void on_add_clicked();

private:
    /**
     * @brief Builds UI based on current mode.
     */
    void build_UI();
    /**
     * @brief Clears current UI elements.
     */
    void clear_UI();
    /**
     * @brief Builds UI in VIEW mode.
     */
    void build_view_mode();
    /**
     * @brief Builds UI in EDIT mode.
     */
    void build_edit_mode();
    /**
     * @brief Builds UI in ADD mode.
     */
    void build_add_mode();
    /// @brief Currently displayed card (nullptr in ADD mode)
    shared_ptr<Card> card_;
    /// @brief Field types for the deck
    shared_ptr<Fields> fields_;
    /// @brief Current UI mode
    Mode mode_;
    /// @brief Layout for dynamically created UI elements
    QVBoxLayout* layout_;
    /// @brief Widgets for input fields (QLineEdit / QLabel depending on mode)
    vector<QWidget*> field_widgets_;
    /// @brief Action button (Edit / Save / Add)
    QPushButton* action_button_;
};

#endif // CARDWIDGET_HH
