#ifndef CARDWIDGET_HH
#define CARDWIDGET_HH
#include "card.hh"
#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>

using namespace std;

class CardWidget : public QWidget
{
    Q_OBJECT

public:
    enum Mode {
        VIEW,
        EDIT,
        ADD
    };

    CardWidget(shared_ptr<Card> card,
               shared_ptr<Fields> fields,
               Mode mode,
               QWidget* parent = nullptr);
    ~CardWidget();
signals:
    void addCardRequested(const Fields& values);
    void cardUpdated(const Fields& values);

private slots:
    void onSaveClicked();
    void onEditClicked();
    void onAddClicked();

private:
    void buildUI();
    void clearUI();

    void buildViewMode();
    void buildEditMode();
    void buildAddMode();

    shared_ptr<Card> card_;
    shared_ptr<Fields> fields_;
    Mode mode_;

    QVBoxLayout* layout_;

    std::vector<QWidget*> fieldWidgets_;
    QPushButton* actionButton_;
};

#endif // CARDWIDGET_HH
