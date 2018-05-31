//
// Created by chris on 5/31/18.
//

#ifndef GTKMM_MVC_TEST_INTEGERCOLUMN_H
#define GTKMM_MVC_TEST_INTEGERCOLUMN_H


#include <gtkmm.h>

class IntegerColumn : public Gtk::TreeModel::ColumnRecord {
public:
    IntegerColumn();

    Gtk::TreeModelColumn<int> m_col_val;
    Gtk::TreeModelColumn<std::string> m_col_desc;
};


#endif //GTKMM_MVC_TEST_INTEGERCOLUMN_H
