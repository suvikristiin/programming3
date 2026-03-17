#include "list.hh"
#include <memory>
#include <iostream>

using namespace std;

List::List() : first_(nullptr), last_(nullptr)
{

}

List::~List()
{

}

void List::insert_at_the_beginning(int i)
{

    shared_ptr<List_item> new_item = make_shared<List_item>(List_item{i, first_});
    first_ = new_item;

    if (last_ == nullptr) {
        last_ = new_item;
    }
}

void List::insert_at_the_end(int i)
{
    shared_ptr<List_item> new_item = make_shared<List_item>(List_item{i, nullptr});


    if (last_ == nullptr) {
        first_ = new_item;
        last_ = new_item;
    } else {
        last_->next = new_item;
        last_ = new_item;
    }

}

void List::remove_first()
{

    if ( first_ == nullptr) {
        return;
    }

    first_ = first_->next;


}

void List::remove_last()
{

    shared_ptr<List_item> item_ptr = first_;

    if (first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;

        return;
    }

    while ( item_ptr != nullptr ) {

        if (item_ptr->next == last_) {
            item_ptr->next = nullptr;
            last_ = item_ptr;

        } else {
            item_ptr = item_ptr->next;
        }
    }







}

void List::print()
{
    shared_ptr<List_item> printable_ptr = first_;
    int running_number = 1;

    if (printable_ptr == nullptr) {
        cout << "No elements" <<endl;
        return;
    } else {
        cout << "List elements: ";
    }

    while ( printable_ptr != nullptr ) {

        cout << printable_ptr->data << " ";
        ++running_number;
        printable_ptr = printable_ptr->next;
    }

    cout << endl;

}
