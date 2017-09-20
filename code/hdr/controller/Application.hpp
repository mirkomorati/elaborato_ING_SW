//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
#define ELABORATO_ING_SW_PATIENTCONTROLLER_HPP

#include "../view/Application.hpp"
#include "Main.hpp"
#include "../model/Doctor.hpp"
#include "SelectDateByDialog.hpp"
#include "AddPatientDialog.hpp"
#include "AddPrescriptionDialog.hpp"
#include "../interfaces/ISubject.hpp"
#include "../model/Application.hpp"

namespace mm {
    namespace controller {

        /*class Application {
        public:
            Application();

            virtual ~Application();

            void set_view(view::Application *patient_view);

            void set_doctor(int doctor_id);

            model::Doctor get_doctor();

            void set_prescription_tree_view(std::string patient_id);

            void add_patient_handler();

            void add_prescription_handler();

            void remove_patient_handler();

            void edit_patient_handler();

            void row_selected_handler(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *column);

            void select_date_by_handler();

            void mask_by_selected_date(util::DateBy date);

            void unselect_patient();

        private:
            view::Application *patient_view;
            model::Doctor doctor;
            model::Patient::TreeModel patient_tree_model;
            Glib::RefPtr<Gtk::ListStore> patient_list_store;
            model::Prescription::TreeModel prescription_tree_model;
            Glib::RefPtr<Gtk::ListStore> prescription_list_store;
            Glib::RefPtr<Gtk::ListStore> drug_list_store;
            model::Drug::TreeModel drug_tree_model;

            void set_drugs_tree_view(const string &patient_id);
        };*/

        class Application : public ISubject {

        public:
            Application();

            void set_doctor(int doctor_id);

            model::Doctor get_doctor();

            void set_prescription_tree_view(std::string patient_id);

            void add_patient_handler();

            void add_prescription_handler();

            void remove_patient_handler();

            void edit_patient_handler();

            void row_selected_handler(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *column);

            void select_date_by_handler();

            void mask_by_selected_date(util::DateBy date);

            void unselect_patient();

        private:
            std::shared_ptr<model::Application> model;


        };
    }
}

#endif //ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
