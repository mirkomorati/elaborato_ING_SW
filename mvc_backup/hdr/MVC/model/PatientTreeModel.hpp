//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTTREEMODEL_HPP
#define ELABORATO_ING_SW_PATIENTTREEMODEL_HPP

#include <gtkmm/treemodel.h>
#include "MainModel.hpp"

namespace mm {
    class PatientTreeModel {
    public:
        PatientTreeModel(MainModel *parent);

    private:
        PatientCols cols;
        MainModel *parent;
    };

    class PatientCols : public Gtk::TreeModel::ColumnRecord {
    public:
        PatientCols() {
            // This order must match the column order in the .glade file
            add(first_name);
            add(second_name);
            add(fiscal_code);
        }

        // These types must match those for the controller in the .glade file
        Gtk::TreeModelColumn<Glib::ustring> first_name;
        Gtk::TreeModelColumn<Glib::ustring> second_name;
        Gtk::TreeModelColumn<Glib::ustring> fiscal_code;

    };
}


#endif //ELABORATO_ING_SW_PATIENTTREEMODEL_HPP
