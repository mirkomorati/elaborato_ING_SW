//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/controller/PatientController.hpp"
#include "../../hdr/DBMaster.hpp"

void mm::PatientController::set_view(PatientView *view) {
    this->patient_view = view;
}

void mm::PatientController::set_parent(mm::MainController *parent) {
    this->parent = parent;
}

void mm::PatientController::add_patient_handler() {
    std::cout << "Add Patient Click" << std::endl;
    patient_view->add_patient_show_dialog();
}

void mm::PatientController::remove_patient_handler() {
    std::cout << "Remove Patient Click" << std::endl;
}

void mm::PatientController::edit_patient_handler() {
    std::cout << "Edit Patient Click" << std::endl;
}

void mm::PatientController::set_doctor(int doctor_id) {
    DBMaster::get_instance().extract_from_db(doctor, doctor_id);
    auto &patients = doctor.get_patients();

    patient_list_store = Gtk::ListStore::create(patient_tree_model);

    auto row = *patient_list_store->append();

    for (int i = 0; i < patients.size(); i++) {
        row[patient_tree_model.first_name] = patients[i].get_first_name();
        row[patient_tree_model.last_name] = patients[i].get_last_name();
        row[patient_tree_model.fiscal_code] = patients[i].get_fiscal_code();

        if (i < patients.size() - 1)
            row = *(patient_list_store->append()++);
    }

    patient_view->set_patient_tree_model(patient_tree_model, patient_list_store);
}
