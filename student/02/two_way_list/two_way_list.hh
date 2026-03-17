#ifndef TWO_WAY_LIST_HH
#define TWO_WAY_LIST_HH

#include <memory>

using namespace std;

class TwoWayList {
public:
    TwoWayList();
    int length() const;
    bool has_value(int value) const;
    void print() const;
    void print_reverse() const;
    bool remove_value(int removable_item);
    void remove_duplicates();
    bool insert_in_numerical_order(int insertable_item);
    // No destructor (!)

private:
    struct List_item {
        int                    data;
        shared_ptr<List_item>  next;
        weak_ptr<List_item>    prev;
    };

    shared_ptr<List_item> first_;
    weak_ptr<List_item>   last_;
    int                   count_;
};

#endif


