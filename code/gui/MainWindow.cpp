//
// Created by Noè Murr on 29/11/2017.
//

#include <gtkmm/button.h>
#include "MainWindow.hpp"
#include "../RefBuilder.hpp"
#include "AddPatientDialog.hpp"
#include "../model/Doctor.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"

bool mm::MainWindow::init() {
    Gtk::TreeView *patientTreeView;
    Gtk::TreeView *prescriptionTreeView;
    Gtk::ToolButton *add_patient_button;
    Gtk::ToolButton *add_prescription_button;

    RefBuilder::get_instance().get_widget("prescriptionTreeView", prescriptionTreeView);
    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);
    RefBuilder::get_instance().get_widget("addPatient", add_patient_button);
    RefBuilder::get_instance().get_widget("addPrescription", add_prescription_button);

    add_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPatientClicked));
    add_prescription_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPrescriptionClicked));
    patientTreeView->signal_row_activated().connect(sigc::mem_fun(this, &mm::MainWindow::onSelectedPatient));


    // setting the tree view
    patientTreeView->append_column("Nome", model::Patient::patientTreeModel.first_name);
    patientTreeView->append_column("Cognome", model::Patient::patientTreeModel.last_name);
    patientTreeView->append_column("Cod. Fiscale", model::Patient::patientTreeModel.fiscal_code);
    patientTreeView->set_model(patientListStore);

    for (int i = 0; i <= 2; i++) {
        patientTreeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
    }

    prescriptionTreeView->append_column("Paziente", model::Prescription::prescriptionTreeModel.patient_id);
    prescriptionTreeView->append_column("ID", model::Prescription::prescriptionTreeModel.prescription_id);
    prescriptionTreeView->append_column("Data Emissione", model::Prescription::prescriptionTreeModel.issue_date);
    prescriptionTreeView->append_column("Data Scadenza", model::Prescription::prescriptionTreeModel.expire_date);
    prescriptionTreeView->append_column("Farmaci", model::Prescription::prescriptionTreeModel.drug_ids);
    prescriptionTreeView->append_column("Interazioni",
                                        model::Prescription::prescriptionTreeModel.negative_interactions);
    prescriptionTreeView->append_column("Usata", model::Prescription::prescriptionTreeModel.used);

    for (int i = 0; i < 7; i++) {
        prescriptionTreeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
        prescriptionTreeView->get_column(i)->set_min_width(100);
        prescriptionTreeView->get_column(i)->set_resizable(true);
        prescriptionTreeView->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        prescriptionTreeView->get_column_cell_renderer(i)->set_property("ellipsize",
                                                                        Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    prescriptionTreeView->set_model(prescriptionListStore);

    // updating the view for the first time

    updatePatientTreeView();

    return true;
}

mm::WindowName mm::MainWindow::getName() const {
    return MAIN;
}

mm::WindowName mm::MainWindow::getNextWindow() const {
    return next;
}

mm::MainWindow::MainWindow() :
        next(MAIN),
        patientListStore(Gtk::ListStore::create(model::Patient::patientTreeModel)),
        prescriptionListStore(Gtk::ListStore::create(model::Prescription::prescriptionTreeModel)),
        selectedPatient("") {}

void mm::MainWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);

    updatePatientTreeView();
    updatePrescriptionTreeView();
}

void mm::MainWindow::onAddPrescriptionClicked() {
    // todo
}

void mm::MainWindow::onAddPatientClicked() {
    std::unique_ptr<Dialog> dialog(new AddPatientDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
}

void mm::MainWindow::updatePatientTreeView() {
    model::Doctor doctor;
    std::vector<model::Patient> patients;
    Gtk::TreeView *patientTreeView;

    try {
        DBMaster::get_instance().extract_from_db(doctor, model::authentication::Login::get_instance().regional_id);
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the doctor from the db...");
    }

    patients = doctor.get_patients();
    patientListStore->clear();

    auto row = *patientListStore->append();

    for (size_t i = 0; i < patients.size(); i++) {
        row[model::Patient::patientTreeModel.first_name] = patients[i].get_first_name();
        row[model::Patient::patientTreeModel.last_name] = patients[i].get_last_name();
        row[model::Patient::patientTreeModel.fiscal_code] = patients[i].get_fiscal_code();
        row[model::Patient::patientTreeModel.health_code] = patients[i].get_health_code();
        row[model::Patient::patientTreeModel.birth_date] = patients[i].get_birth_date();
        row[model::Patient::patientTreeModel.birth_place] = patients[i].get_birth_place();
        row[model::Patient::patientTreeModel.address] = patients[i].get_address();
        row[model::Patient::patientTreeModel.risk_factors] = patients[i].get_risk_factors();


        if (i < patients.size() - 1)
            row = *(patientListStore->append()++);
    }
}

void mm::MainWindow::updatePrescriptionTreeView() {
    Gtk::TreeView *patientTreeView;
    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);
    auto sel = patientTreeView->get_selection()->get_selected();

    if (not sel) return;

    Glib::ustring patientId = static_cast<Glib::ustring>((*sel)[model::Patient::patientTreeModel.health_code]);
    model::Patient patient;
    std::vector<model::Prescription> prescriptions;

    try {
        DBMaster::get_instance().extract_from_db(patient, static_cast<std::string>(patientId));
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    prescriptions = patient.get_prescriptions();

    prescriptionListStore->clear();
    auto row = *prescriptionListStore->append();

    for (size_t i = 0; i < prescriptions.size(); i++) {
        row[model::Prescription::prescriptionTreeModel.patient_id] = std::to_string(prescriptions[i].get_patient_id());
        row[model::Prescription::prescriptionTreeModel.prescription_id] = std::to_string(
                prescriptions[i].get_prescription_id());
        row[model::Prescription::prescriptionTreeModel.issue_date] = prescriptions[i].get_issue_date();
        row[model::Prescription::prescriptionTreeModel.expire_date] = prescriptions[i].get_expire_date();
        row[model::Prescription::prescriptionTreeModel.drug_ids] = prescriptions[i].get_drug_ids_as_string();
        row[model::Prescription::prescriptionTreeModel.negative_interactions] = prescriptions[i].get_negative_interactions();
        row[model::Prescription::prescriptionTreeModel.used] = prescriptions[i].is_used() ? "si" : "no";

        if (i < prescriptions.size() - 1)
            row = *(prescriptionListStore->append()++);
    }

}

void mm::MainWindow::onSelectedPatient(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *) {
    updatePrescriptionTreeView();
}
