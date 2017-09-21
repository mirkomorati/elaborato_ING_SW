#include <utility>

#include "../../hdr/controller/Application.hpp"
#include "../../hdr/factory/DialogFactory.hpp"
#include "../../hdr/DBMaster.hpp"

//
// Created by Noè Murr on 03/07/2017.
//

mm::model::Doctor mm::controller::Application::get_doctor() {
    lock_guard<mutex> lg(model->mutex);
    return model->doctor;
}

void mm::controller::Application::add_patient_handler() {
    factory::DialogFactory::get_instance()->create_dialog("AddPatientDialog")->show_dialog();
}

void mm::controller::Application::add_prescription_handler() {
    factory::DialogFactory::get_instance()->create_dialog("AddPrescriptionDialog")->show_dialog();
}

void mm::controller::Application::remove_patient_handler() {
    // todo implement
}

void mm::controller::Application::edit_patient_handler() {
    // todo implement
}

void mm::controller::Application::select_date_by_handler() {
    factory::DialogFactory::get_instance()->create_dialog("SelectDateByDialog")->show_dialog();
}

void mm::controller::Application::mask_by_selected_date(mm::util::DateBy date) {
    std::cout << "Masking by : " << date.date.day << date.date.month << date.date.year << " by " << date.by
              << std::endl;
}

void mm::controller::Application::unselect_patient() {
    lock_guard<mutex> lg(model->mutex);
    model->drug_tree_view_row_selected = false;
    model->patient_tree_row_selected = false;
    model->prescription_tree_view_row_selected = false;
    notify();
}

void mm::controller::Application::set_prescription_tree_view(std::string patient_id) {
    lock_guard<mutex> lg(model->mutex);
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, std::move(patient_id));
    } catch (record_not_found_error &e) {
        model->prescription_list_store.clear();
        return;
    }

    auto &prescriptions = patient.get_prescriptions();
    model->prescription_list_store.clear();

    auto row = *model->prescription_list_store->append();

    for (size_t i = 0; i < prescriptions.size(); i++) {
        row[model->prescription_tree_model.patient_id] = std::to_string(
                prescriptions[i].get_patient_id());
        row[model->prescription_tree_model.prescription_id] = std::to_string(
                prescriptions[i].get_prescription_id());
        row[model->prescription_tree_model.issue_date] = prescriptions[i].get_issue_date();
        row[model->prescription_tree_model.expire_date] = prescriptions[i].get_expire_date();
        row[model->prescription_tree_model.drug_ids] = prescriptions[i].get_drug_ids_as_string();
        row[model->prescription_tree_model.negative_interactions] = prescriptions[i].get_negative_interactions();
        row[model->prescription_tree_model.used] = prescriptions[i].is_used() ? "si" : "no";

        if (i < prescriptions.size() - 1)
            row = *(model->prescription_list_store->append()++);
    }

    notify();
}

void mm::controller::Application::set_doctor(int doctor_id) {
    lock_guard<mutex> lg(model->mutex);
    if (doctor_id == model->doctor.get_regional_id()) {
        model->patient_list_store.clear();
    } else {

        try {
            DBMaster::get_instance().extract_from_db(model->doctor, doctor_id);
        } catch (record_not_found_error &e) {
            model->patient_tree_row_selected = false;
            return;
        }
    }

    auto &patients = model->doctor.get_patients();

    model->patient_list_store.clear();

    auto row = *model->patient_list_store->append();

    for (size_t i = 0; i < patients.size(); i++) {
        row[model->patient_tree_model.first_name] = patients[i].get_first_name();
        row[model->patient_tree_model.last_name] = patients[i].get_last_name();
        row[model->patient_tree_model.fiscal_code] = patients[i].get_fiscal_code();
        row[model->patient_tree_model.health_code] = patients[i].get_health_code();
        row[model->patient_tree_model.birth_date] = patients[i].get_birth_date();
        row[model->patient_tree_model.birth_place] = patients[i].get_birth_place();
        row[model->patient_tree_model.address] = patients[i].get_address();
        row[model->patient_tree_model.risk_factors] = patients[i].get_risk_factors();

        if (i < patients.size() - 1)
            row = *(model->patient_list_store->append()++);
    }

    notify();
}

void mm::controller::Application::row_selected_handler(const Gtk::TreeModel::Path &path,
                                                       Gtk::TreeViewColumn *column) {
    lock_guard<mutex> lg(model->mutex);

    auto selection = column->get_tree_view()->get_selection();
    auto iter = model->patient_list_store->get_iter(path);
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        std::cout << "Row activated: first name = ";
        std::cout << row[model->patient_tree_model.first_name]
                  << ", last name = "
                  << row[model->patient_tree_model.last_name]
                  << ", fiscal code = "
                  << row[model->patient_tree_model.fiscal_code] << std::endl;
        model->selected_patient_row = row;
        selection->unselect_all();
        auto patient_id = static_cast<Glib::ustring>(row[model->patient_tree_model.health_code]);
        set_prescription_tree_view(patient_id.raw());
        set_drugs_tree_view(patient_id.raw());
    }
}

void mm::controller::Application::set_drugs_tree_view(const string &patient_id) {
    lock_guard<mutex> lg(model->mutex);
    std::vector<model::Drug> drugs;
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patient_id);
    } catch (record_not_found_error &e) {
        // todo cerca di capirci qualcosa.
        return;
    }

    auto &prescriptions = patient.get_prescriptions();

    for (auto &prescription : prescriptions) {
        auto drug_ids = prescription.get_drug_ids();
        for (auto &drug : drug_ids) {
            model::Drug tmp;
            DBMaster::get_instance().extract_from_db(tmp, {drug.first, drug.second});
            drugs.push_back(tmp);
        }
    }

    model->drug_list_store.clear();
    auto row = *model->drug_list_store->append();

    for (size_t i = 0; i < drugs.size(); i++) {
        row[model->drug_tree_model.name] = drugs[i].get_name();
        row[model->drug_tree_model.pharmaceutical_form] = drugs[i].get_pharmaceutical_form();
        row[model->drug_tree_model.ATC_classification] = drugs[i].get_ATC_classification();
        row[model->drug_tree_model.contraindications] = drugs[i].get_contraindications_as_string();
        row[model->drug_tree_model.active_principles] = drugs[i].get_active_principles_as_string();
        row[model->drug_tree_model.price] = drugs[i].get_price_as_string();
        if (i < drugs.size() - 1)
            row = *(model->drug_list_store->append()++);
    }
}

shared_ptr<mm::model::Application> mm::controller::Application::get_model() {
    return model;
}
