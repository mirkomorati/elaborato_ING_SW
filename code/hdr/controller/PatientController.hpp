//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
#define ELABORATO_ING_SW_PATIENTCONTROLLER_HPP

#include "../view/PatientView.hpp"
#include "MainController.hpp"
#include "../model/Doctor.hpp"

namespace mm {
    class PatientView;

    class MainController;

    class PatientController {
    public:
        void set_view(PatientView *patient_view);

        void set_parent(mm::MainController *parent);

        void set_doctor(int doctor_id);

        void set_prescription_tree_view(std::string patient_id);

        void add_patient_handler();

        void remove_patient_handler();

        void edit_patient_handler();

        void row_selected_handler(const Gtk::TreeModel::Path &path,
                                  Gtk::TreeViewColumn *column);

        void on_add_patient_dialog_ok_handler();

        void on_add_patient_dialog_cancel_handler();

        void select_date_handler();

    private:
        PatientView *patient_view;
        MainController *parent;
        Doctor doctor;
        Patient::TreeModel patient_tree_model;
        Glib::RefPtr<Gtk::ListStore> patient_list_store;
        Prescription::TreeModel prescription_tree_model;
        Glib::RefPtr<Gtk::ListStore> prescription_list_store;
    };
}

#endif //ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
