//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTVIEW_HPP
#define ELABORATO_ING_SW_PATIENTVIEW_HPP

#include <gtkmm/toolbutton.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/grid.h>
#include "../controller/PatientController.hpp"
#include "../model/PatientTreeModel.hpp"
#include "../model/PrescriptionTreeModel.hpp"

namespace mm {
    class PatientController;

    class PatientView {
    public:
        PatientView(PatientController *controller);

        void set_patient_tree_model(PatientTreeModel &patient_tree_model,
                                    Glib::RefPtr<Gtk::ListStore> patient_list_store);

        void set_prescription_tree_model(
            PrescriptionTreeModel &prescription_tree_model,
            Glib::RefPtr<Gtk::ListStore> prescription_list_store);

        void add_patient_show_dialog();

        void dispose_add_patient_dialog();

        void patient_detail_show(Gtk::TreeModel::Row row,
                                 PatientTreeModel &patient_tree_model);

        void show_select_date_dialog();

    private:
        PatientController *controller;

        Gtk::ToolButton *add_patient;
        Gtk::ToolButton *edit_patient;
        Gtk::ToolButton *remove_patient;
        Gtk::TreeView *patient_tree_view;
        Gtk::TreeView *prescription_tree_view;
        Gtk::Grid *patient_detail;
    };
}


#endif //ELABORATO_ING_SW_PATIENTVIEW_HPP
