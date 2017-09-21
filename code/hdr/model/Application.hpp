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
            std::pair<Doctor, bool> doctor;
            std::pair<Patient::TreeModel, bool> patient_tree_model;
            std::pair<Prescription::TreeModel, bool> prescription_tree_model;
            std::pair<Drug::TreeModel, bool> drug_tree_model;
            std::pair<Glib::RefPtr<Gtk::ListStore>, bool> patient_list_store;
            std::pair<Glib::RefPtr<Gtk::ListStore>, bool> prescription_list_store;
            std::pair<Glib::RefPtr<Gtk::ListStore>, bool> drug_list_store;
            std::pair<bool, bool> patient_tree_row_selected;
            std::pair<bool, bool> prescription_tree_view_row_selected;
            std::pair<bool, bool> drug_tree_view_row_selected;
            std::pair<Gtk::TreeModel::Row, bool> selected_patient_row;

            Application() {
                doctor.second = false;
                patient_tree_model.second = false;
                prescription_tree_model.second = false;
                drug_tree_model.second = false;
                patient_list_store.second = false;
                patient_list_store.first = Gtk::ListStore::create(patient_tree_model.first);
                prescription_list_store.second = false;
                prescription_list_store.first = Gtk::ListStore::create(prescription_tree_model.first);
                drug_list_store.second = false;
                drug_list_store.first = Gtk::ListStore::create(drug_tree_model.first);
                patient_tree_row_selected.second = false;
                prescription_tree_view_row_selected.second = false;
                drug_tree_view_row_selected.second = false;
                selected_patient_row.second = false;
            };
        };

        /*
         * Application() :
                    doctor(Doctor(), false),
                    patient_tree_model(Patient::TreeModel(),false),
                    prescription_tree_model(Prescription::TreeModel(), false),
                    drug_tree_model(Drug::TreeModel(),false),
                    patient_list_store(Gtk::ListStore::create(patient_tree_model.first),false),
                    prescription_list_store(Gtk::ListStore::create(prescription_tree_model.first), false),
                    drug_list_store(Gtk::ListStore::create(drug_tree_model.first), false),
                    patient_tree_row_selected(false, false),
                    prescription_tree_view_row_selected(false, false),
                    drug_tree_view_row_selected(false, false),
                    selected_patient_row(Gtk::TreeModel::Row(), false) {};
         * */
    }
}


#endif //ELABORATO_ING_SW_APPLICATION_HPP
