#include "cardwidget.hh"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>

CardWidget::CardWidget(shared_ptr<Card> card,
                       shared_ptr<Fields> fields,
                       Mode mode,
                       QWidget* parent)
    : QWidget(parent),
    card_(card),
    fields_(fields),
    mode_(mode),
    layout_(new QVBoxLayout(this)),
    actionButton_(nullptr)
{
    setLayout(layout_);
    buildUI();
}

CardWidget::~CardWidget()
{

}

void CardWidget::clearUI()
{
    while (QLayoutItem* item = layout_->takeAt(0))
    {
        if (QWidget* w = item->widget())
        {
            w->setParent(nullptr);
            w->deleteLater();
        }
        delete item;
    }

    fieldWidgets_.clear();
    actionButton_ = nullptr;
}

void CardWidget::buildUI()
{
    clearUI();

    if (mode_ == VIEW)
        buildViewMode();
    else if (mode_ == EDIT)
        buildEditMode();
    else if (mode_ == ADD)
        buildAddMode();
}

void CardWidget::buildViewMode()
{
    Fields values;

    card_->get_definitions(*fields_, values);

    for (size_t i = 0; i < fields_->size(); ++i)
    {
        QLabel* label = new QLabel(
            QString::fromStdString(fields_->at(i) + ": " +
                                   values.at(i)));

        layout_->addWidget(label);
        fieldWidgets_.push_back(label);
    }

    if (actionButton_ == nullptr) {
        actionButton_ = new QPushButton("Edit");
        layout_->addWidget(actionButton_);
    }

    connect(actionButton_, &QPushButton::clicked,
            this, &CardWidget::onEditClicked);
}

void CardWidget::buildEditMode()
{
    Fields values;
    card_->get_definitions(*fields_, values);

    for (size_t i = 0; i < fields_->size(); ++i)
    {
        QLineEdit* edit = new QLineEdit(
            QString::fromStdString(values.at(i)));

        layout_->addWidget(edit);
        fieldWidgets_.push_back(edit);
    }

    actionButton_ = new QPushButton("Save changes");
    layout_->addWidget(actionButton_);

    connect(actionButton_, &QPushButton::clicked,
            this, &CardWidget::onSaveClicked);
}

void CardWidget::buildAddMode()
{
    for (size_t i = 0; i < fields_->size(); ++i)
    {
        QHBoxLayout* rowLayout = new QHBoxLayout();

        QLabel* label = new QLabel(
            QString::fromStdString(fields_->at(i)), this);

        QLineEdit* edit = new QLineEdit(this);

        rowLayout->addWidget(label);
        rowLayout->addWidget(edit);


        layout_->addLayout(rowLayout);

        fieldWidgets_.push_back(edit);
    }

    actionButton_ = new QPushButton("Add card", this);
    layout_->addWidget(actionButton_);

    connect(actionButton_, &QPushButton::clicked,
            this, &CardWidget::onAddClicked);
}

void CardWidget::onAddClicked()
{
    Fields values;

    for (QWidget* w : fieldWidgets_)
    {
        QLineEdit* edit = qobject_cast<QLineEdit*>(w);
        if (edit)
        {
            values.push_back(edit->text().toStdString());
        }
    }

    emit addCardRequested(values);
}

void CardWidget::onEditClicked()
{
    mode_ = EDIT;
    buildUI();
}

void CardWidget::onSaveClicked()
{
    Fields new_values;

    for (auto w : fieldWidgets_)
    {
        QLineEdit* edit = qobject_cast<QLineEdit*>(w);
        if (edit)
        {
            new_values.push_back(edit->text().toStdString());
        }
    }

    if (mode_ == EDIT)
    {
        emit cardUpdated(new_values);
    }

    mode_ = VIEW;
    buildUI();
}











