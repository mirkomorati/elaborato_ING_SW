//
// Created by Noè Murr on 19/09/2017.
//

#ifndef ELABORATO_ING_SW_APPLICATION_HPP
#define ELABORATO_ING_SW_APPLICATION_HPP

#include <gtkmm/liststore.h>
#include "Doctor.hpp"

namespace mm {
    namespace model {
        struct Application {
            std::mutex mutex;
            Doctor doctor;
            Patient::TreeModel patient_tree_model;
            Prescription::TreeModel prescription_tree_model;
            Drug::TreeModel drug_tree_model;
            Glib::RefPtr<Gtk::ListStore> patient_list_store;
            Glib::RefPtr<Gtk::ListStore> prescription_list_store;
            Glib::RefPtr<Gtk::ListStore> drug_list_store;
            bool patient_tree_row_selected;
            bool prescription_tree_view_row_selected;
            bool drug_tree_view_row_selected;
            Gtk::TreeModel::Row selected_patient_row;
        };
    }
}


#endif //ELABORATO_ING_SW_APPLICATION_HPP
