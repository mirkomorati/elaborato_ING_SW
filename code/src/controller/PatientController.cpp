//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/controller/PatientController.hpp"
#include "../../hdr/DBMaster.hpp"
#include "../../hdr/RefBuilder.hpp"

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
        row[patient_tree_model.health_code] = patients[i].get_health_code();
        row[patient_tree_model.birth_date] = patients[i].get_birth_date();
        row[patient_tree_model.birth_place] = patients[i].get_birth_place();
        row[patient_tree_model.address] = patients[i].get_address();
        row[patient_tree_model.risk_factors] = patients[i].get_risk_factors();

        if (i < patients.size() - 1)
            row = *(patient_list_store->append()++);
    }

    patient_view->set_patient_tree_model(patient_tree_model, patient_list_store);
}

void
mm::PatientController::row_selected_handler(const Gtk::TreeModel::Path &path,
                                            Gtk::TreeViewColumn *column) {
    auto iter = patient_list_store->get_iter(path);
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        std::cout << "Row activated: first name = "
                  << row[patient_tree_model.first_name]
                  << ", last name = "
                  << row[patient_tree_model.last_name]
                  << ", fiscal code = "
                  << row[patient_tree_model.fiscal_code] << std::endl;
        patient_view->patient_detail_show(row, patient_tree_model);

        auto patient_id = static_cast<Glib::ustring>(row[patient_tree_model.health_code]);
        set_prescription_tree_view(patient_id.raw());
    }
}

void mm::PatientController::set_prescription_tree_view(std::string patient_id) {
    Patient patient;
    DBMaster::get_instance().extract_from_db(patient, patient_id);

    auto &prescriptions = patient.get_prescriptions();

    prescription_list_store = Gtk::ListStore::create(prescription_tree_model);
    auto row = *prescription_list_store->append();

    for (int i = 0; i < prescriptions.size(); i++) {
        row[prescription_tree_model.patient_id] = std::to_string(
            prescriptions[i].get_patient_id());
        row[prescription_tree_model.prescription_id] = std::to_string(
            prescriptions[i].get_prescription_id());
        row[prescription_tree_model.issue_date] = prescriptions[i].get_issue_date();
        row[prescription_tree_model.expire_date] = prescriptions[i].get_expire_date();
        row[prescription_tree_model.drug_ids] = prescriptions[i].get_drug_ids();
        row[prescription_tree_model.negative_interactions] = prescriptions[i].get_negative_interactions();
        row[prescription_tree_model.used] = prescriptions[i].is_used() ? "si"
                                                                       : "no";

        if (i < prescriptions.size() - 1)
            row = *(prescription_list_store->append()++);
    }

    patient_view->set_prescription_tree_model(prescription_tree_model,
                                              prescription_list_store);
}

void mm::PatientController::on_add_patient_dialog_ok_button_pressed() {
    auto &refBuilder = RefBuilder::get_instance();
    Patient patient;
    stringstream address;
    stringstream birth_address;

    // fields
    Gtk::Entry *first_name;
    Gtk::Entry *last_name;
    Gtk::Entry *fiscal_code;
    Gtk::Entry *health_code;
    Gtk::Entry *birth_date;
    Gtk::Entry *street;
    Gtk::Entry *civic;
    Gtk::Entry *zip_code;
    Gtk::Entry *city;
    Gtk::Entry *country;
    Gtk::Entry *birth_city;
    Gtk::Entry *birth_country;

    refBuilder.get_widget("addFirstName", first_name);
    refBuilder.get_widget("addLastName", last_name);
    refBuilder.get_widget("addFiscalCode", fiscal_code);
    refBuilder.get_widget("addHealthCode", health_code);
    refBuilder.get_widget("addBirthDate", birth_date);
    refBuilder.get_widget("addBirthCity", birth_city);
    refBuilder.get_widget("addBirthCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);

    patient.set_first_name(first_name->get_text());
    patient.set_last_name(last_name->get_text());
    patient.set_fiscal_code(fiscal_code->get_text());
    patient.set_health_code(health_code->get_text());
    patient.set_birth_date(birth_date->get_text());

    address << street->get_text() << " " << civic->get_text() << ", " << zip_code->get_text() << ", "
            << city->get_text() << ", " << country->get_text();

    birth_address << birth_city->get_text() << ", "
                  << birth_country->get_text();

    patient.set_address(address.str());
    patient.set_doctor_id(doctor.get_regional_id());

    DBMaster::get_instance().add_to_db(patient);

    patient_view->dispose_add_patient_dialog();

}

void mm::PatientController::on_add_patient_dialog_cancel_button_pressed() {
    patient_view->dispose_add_patient_dialog();
}
