//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
#define ELABORATO_ING_SW_PATIENTCONTROLLER_HPP

#include "../view/Patient.hpp"
#include "Main.hpp"
#include "../model/Doctor.hpp"
#include "SelectDateDialog.hpp"

namespace mm {
    namespace view {
        class Patient;
    }
    namespace controller {
        class Main;

        class Patient {
        public:
            Patient();

            void set_view(view::Patient *patient_view);

            void set_parent(controller::Main *parent);

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
            view::Patient *patient_view;
            controller::Main *parent;
            model::Doctor doctor;
            model::Patient::TreeModel patient_tree_model;
            Glib::RefPtr<Gtk::ListStore> patient_list_store;
            model::Prescription::TreeModel prescription_tree_model;
            Glib::RefPtr<Gtk::ListStore> prescription_list_store;
            Glib::RefPtr<Gtk::ListStore> drug_list_store;
            model::Drug::TreeModel drug_tree_model;
            controller::SelectDateDialog select_date_controller;

            void set_drugs_tree_view(const string patient_id);
        };
    }
}

#endif //ELABORATO_ING_SW_PATIENTCONTROLLER_HPP