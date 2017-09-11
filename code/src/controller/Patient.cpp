//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/controller/Patient.hpp"
#include "../../hdr/DBMaster.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::controller::Patient::set_view(view::Patient *view) {
    this->patient_view = view;
}

void mm::controller::Patient::set_parent(mm::controller::Main *parent) {
    this->parent = parent;
}

void mm::controller::Patient::add_patient_handler() {
    std::cout << "Add Patient Click" << std::endl;
    patient_view->add_patient_show_dialog();
}

void mm::controller::Patient::remove_patient_handler() {
    std::cout << "Remove Patient Click" << std::endl;

}

void mm::controller::Patient::edit_patient_handler() {
    std::cout << "Edit Patient Click" << std::endl;
}

void mm::controller::Patient::set_doctor(int doctor_id) {

    if (doctor_id == doctor.get_regional_id()) {
        patient_list_store = Gtk::ListStore::create(patient_tree_model);
        patient_view->set_patient_tree_model(patient_tree_model, patient_list_store);
    } else {

        try {
            DBMaster::get_instance().extract_from_db(doctor, doctor_id);
        } catch (record_not_found_error &e) {
            patient_list_store = Gtk::ListStore::create(patient_tree_model);
            patient_view->set_patient_tree_model(patient_tree_model, patient_list_store);
            return;
        }
    }

    auto &patients = doctor.get_patients();

    patient_list_store = Gtk::ListStore::create(patient_tree_model);

    auto row = *patient_list_store->append();

    for (size_t i = 0; i < patients.size(); i++) {
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

void mm::controller::Patient::row_selected_handler(const Gtk::TreeModel::Path &path,
                                                   Gtk::TreeViewColumn *column) {
    auto selection = column->get_tree_view()->get_selection();
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
        selection->unselect_all();
        auto patient_id = static_cast<Glib::ustring>(row[patient_tree_model.health_code]);
        set_prescription_tree_view(patient_id.raw());
        set_drugs_tree_view(patient_id.raw());
    }
}

void mm::controller::Patient::set_prescription_tree_view(std::string patient_id) {
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patient_id);
    } catch (record_not_found_error &e) {
        prescription_list_store = Gtk::ListStore::create(prescription_tree_model);
        patient_view->set_prescription_tree_model(prescription_tree_model, prescription_list_store);
        doctor = model::Doctor();
        return;
    }

    auto &prescriptions = patient.get_prescriptions();

    prescription_list_store = Gtk::ListStore::create(prescription_tree_model);
    auto row = *prescription_list_store->append();

    for (size_t i = 0; i < prescriptions.size(); i++) {
        row[prescription_tree_model.patient_id] = std::to_string(
            prescriptions[i].get_patient_id());
        row[prescription_tree_model.prescription_id] = std::to_string(
            prescriptions[i].get_prescription_id());
        row[prescription_tree_model.issue_date] = prescriptions[i].get_issue_date();
        row[prescription_tree_model.expire_date] = prescriptions[i].get_expire_date();
        row[prescription_tree_model.drug_ids] = prescriptions[i].get_drug_ids_as_string();
        row[prescription_tree_model.negative_interactions] = prescriptions[i].get_negative_interactions();
        row[prescription_tree_model.used] = prescriptions[i].is_used() ? "si" : "no";

        if (i < prescriptions.size() - 1)
            row = *(prescription_list_store->append()++);
    }

    patient_view->set_prescription_tree_model(prescription_tree_model,
                                              prescription_list_store);
}

void mm::controller::Patient::set_drugs_tree_view(const string patient_id) {
    std::vector<std::string> drug_ids;
    std::vector<model::Drug> drugs;
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patient_id);
    } catch (record_not_found_error &e) {
        drug_list_store = Gtk::ListStore::create(drug_tree_model);
        patient_view->set_drug_tree_model(drug_tree_model, drug_list_store);
        return;
    }

    auto &prescriptions = patient.get_prescriptions();

    for (auto &prescription : prescriptions)
        for (auto &drug : prescription.get_drug_ids())
            drug_ids.push_back(drug);

    for (auto &drug : drug_ids) {
        model::Drug tmp;
        DBMaster::get_instance().extract_from_db(tmp, drug);
        drugs.push_back(tmp);
    }

    drug_list_store = Gtk::ListStore::create(drug_tree_model);
    auto row = *drug_list_store->append();

    for (size_t i = 0; i < drugs.size(); i++) {
        row[drug_tree_model.name] = drugs[i].get_name();
        row[drug_tree_model.pharmaceutical_form] = drugs[i].get_pharmaceutical_form();
        row[drug_tree_model.ATC_classification] = drugs[i].get_ATC_classification();
        row[drug_tree_model.contraindications] = drugs[i].get_contraindications_as_string();
        row[drug_tree_model.active_principles] = drugs[i].get_active_principles_as_string();
        row[drug_tree_model.price] = drugs[i].get_price_as_string();
        if (i < drugs.size() - 1)
            row = *(drug_list_store->append()++);
    }

    patient_view->set_drug_tree_model(drug_tree_model, drug_list_store);

}

void mm::controller::Patient::on_add_patient_dialog_ok_handler() {
    auto &refBuilder = RefBuilder::get_instance();
    model::Patient patient;
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

void mm::controller::Patient::on_add_patient_dialog_cancel_handler() {
    patient_view->dispose_add_patient_dialog();
}

void mm::controller::Patient::select_date_handler() {
    select_date_controller->set_parent(this);
    select_date_controller->show_dialog();
}

mm::controller::Patient::Patient() {
    select_date_controller = new SelectDateDialog();
    select_date_controller->set_view();
}

void mm::controller::Patient::unselect_patient() {
    set_doctor(doctor.get_regional_id());
    set_drugs_tree_view("");
    set_prescription_tree_view("");
}

void mm::controller::Patient::mask_by_selected_date(mm::util::DateBy date) {
    std::cout << "Masking by : " << date.date.day << date.date.month << date.date.year << " by " << date.by
              << std::endl;
}

mm::controller::Patient::~Patient() {
    delete (select_date_controller);
}

