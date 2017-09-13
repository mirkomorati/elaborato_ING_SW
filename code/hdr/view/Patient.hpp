//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTVIEW_HPP
#define ELABORATO_ING_SW_PATIENTVIEW_HPP

#include <gtkmm/toolbutton.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/grid.h>
#include "../controller/Patient.hpp"
#include "../model/Patient.hpp"
#include "../model/Prescription.hpp"

namespace mm {
    namespace controller {
        class Patient;
    }
    namespace view {

        class Patient {
        public:
            explicit Patient(controller::Patient *controller);

            // todo potrebbe esserci un segfault controlla oggetto tmp.
            void set_patient_tree_model(model::Patient::TreeModel &patient_tree_model,
                                        Glib::RefPtr<Gtk::ListStore> patient_list_store);

            void unset_patient_model() const;

            void set_prescription_tree_model(
                    model::Prescription::TreeModel &prescription_tree_model,
                    Glib::RefPtr<Gtk::ListStore> prescription_list_store);

            void unset_prescription_model() const;

            void set_drug_tree_model(
                    model::Drug::TreeModel &drug_tree_model,
                    Glib::RefPtr<Gtk::ListStore> drug_list_store);

            void unset_drug_model() const;

            void unselect_patient() const;

            void unselect_prescription() const;

            void unselect_drug() const;


            void add_patient_show_dialog();

            void dispose_add_patient_dialog();

            void patient_detail_show(Gtk::TreeModel::Row row,
                                     model::Patient::TreeModel &patient_tree_model);

        private:
            controller::Patient *controller;
            Gtk::ToolButton *add_patient;
            Gtk::ToolButton *edit_patient;
            Gtk::ToolButton *remove_patient;
            Gtk::TreeView *patient_tree_view;
            Gtk::TreeView *prescription_tree_view;
            Gtk::TreeView *drug_tree_view;
            Gtk::Grid *patient_detail;
        };
    }
}


#endif //ELABORATO_ING_SW_PATIENTVIEW_HPP
