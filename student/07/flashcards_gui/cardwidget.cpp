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
    mode_(mode)
{
    layout_ = new QVBoxLayout(this);
    action_button_ = nullptr;
    build_UI();
}

CardWidget::~CardWidget()
{

}

void CardWidget::clear_UI() {

    while (QLayoutItem* item = layout_->takeAt(0)) {
        if (QWidget* w = item->widget()) {
            w->setParent(nullptr);
            w->deleteLater();
        }

        delete item;
    }

    field_widgets_.clear();
    action_button_ = nullptr;
}

void CardWidget::build_UI() {
    clear_UI();

    if (mode_ == VIEW)
        build_view_mode();
    else if (mode_ == EDIT)
        build_edit_mode();
    else if (mode_ == ADD)
        build_add_mode();
}

void CardWidget::build_view_mode() {

    Fields values;
    card_->get_definitions(*fields_, values);

    for (size_t i = 0; i < fields_->size(); ++i) {
        QLabel* label = new QLabel(QString::fromStdString(fields_->at(i) + ": " + values.at(i)));
        layout_->addWidget(label);
        field_widgets_.push_back(label);
    }

    if (action_button_ == nullptr) {
        action_button_ = new QPushButton("Edit");
        layout_->addWidget(action_button_);
    }

    connect(action_button_, &QPushButton::clicked,
            this, &CardWidget::on_edit_clicked);
}

void CardWidget::build_edit_mode() {

    Fields values;
    card_->get_definitions(*fields_, values);

    for (size_t i = 0; i < fields_->size(); ++i) {
        QLineEdit* edit = new QLineEdit(QString::fromStdString(values.at(i)));
        layout_->addWidget(edit);
        field_widgets_.push_back(edit);
    }

    action_button_ = new QPushButton("Save changes");
    layout_->addWidget(action_button_);
    connect(action_button_, &QPushButton::clicked,
            this, &CardWidget::on_save_clicked);
}

void CardWidget::build_add_mode() {

    for (size_t i = 0; i < fields_->size(); ++i) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        QLabel* label = new QLabel(QString::fromStdString(fields_->at(i)), this);
        QLineEdit* edit = new QLineEdit(this);
        rowLayout->addWidget(label);
        rowLayout->addWidget(edit);
        layout_->addLayout(rowLayout);
        field_widgets_.push_back(edit);
    }

    action_button_ = new QPushButton("Add card", this);
    layout_->addWidget(action_button_);
    connect(action_button_, &QPushButton::clicked,
            this, &CardWidget::on_add_clicked);
}

void CardWidget::on_add_clicked() {

    Fields values;

    for (QWidget* w : field_widgets_) {
        QLineEdit* edit = qobject_cast<QLineEdit*>(w);

        if (edit) {
            values.push_back(edit->text().toStdString());
        }
    }

    emit add_card_requested(values);
}

void CardWidget::on_edit_clicked() {

    mode_ = EDIT;
    build_UI();
}

void CardWidget::on_save_clicked() {

    Fields new_values;

    for (auto w : field_widgets_) {
        QLineEdit* edit = qobject_cast<QLineEdit*>(w);

        if (edit) {
            new_values.push_back(edit->text().toStdString());
        }
    }

    if (mode_ == EDIT) {
        emit card_updated(new_values);
    }

    mode_ = VIEW;
    build_UI();
}











