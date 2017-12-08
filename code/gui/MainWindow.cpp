//
// Created by Noè Murr on 29/11/2017.
//

#include <gtkmm/button.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "MainWindow.hpp"
#include "RefBuilder.hpp"
#include "AddPatientDialog.hpp"
#include "../model/Doctor.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"
#include "AddPrescriptionDialog.hpp"
#include "AboutDialog.hpp"

mm::MainWindow::MainWindow() :
        next(MAIN),
        patientListStore(Gtk::ListStore::create(model::Patient::patientTreeModel)) {}

void mm::MainWindow::initHandlers() {
    auto refBuilder = RefBuilder::get_instance();

    Gtk::TreeView *patientTreeView;
    Gtk::ToolButton *add_patient_button;
    Gtk::ToolButton *add_prescription_button;
    Gtk::ToolButton *remove_patient_button;
    Gtk::MenuItem *logoutMenuItem;
    Gtk::ImageMenuItem *aboutMenuItem;

    refBuilder.get_widget("patientTreeView", patientTreeView);
    refBuilder.get_widget("addPatient", add_patient_button);
    refBuilder.get_widget("addPrescription", add_prescription_button);
    refBuilder.get_widget("removePatient", remove_patient_button);
    refBuilder.get_widget("logoutMenuItem", logoutMenuItem);
    refBuilder.get_widget("aboutMenuItem", aboutMenuItem);

    add_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPatientClicked));
    add_prescription_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPrescriptionClicked));
    patientTreeView->signal_row_activated().connect(sigc::mem_fun(this, &mm::MainWindow::onSelectedPatient));
    remove_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onRemovePatientClicked));
    logoutMenuItem->signal_activate().connect(sigc::mem_fun(this, &mm::MainWindow::onLogout));
    aboutMenuItem->signal_activate().connect(sigc::mem_fun(this, &mm::MainWindow::onAboutClicked));
}

void mm::MainWindow::initTreeView() {
    Gtk::TreeView *patientTreeView;

    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);

    patientTreeView->append_column("Nome", model::Patient::patientTreeModel.first_name);
    patientTreeView->append_column("Cognome", model::Patient::patientTreeModel.last_name);
    patientTreeView->append_column("Cod. Fiscale", model::Patient::patientTreeModel.fiscal_code);
    patientTreeView->set_model(patientListStore);

    for (int i = 0; i <= 2; i++) {
        patientTreeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
    }

    updatePatientTreeView();
}

bool mm::MainWindow::init() {
    Gtk::MenuBar *menuBar;
    RefBuilder::get_instance().get_widget("menuBar", menuBar);
    menuBar->set_visible(true);

    initHandlers();
    initTreeView();

    return true;
}

mm::WindowName mm::MainWindow::getName() const {
    return MAIN;
}

mm::WindowName mm::MainWindow::getNextWindow() const {
    return next;
}

void mm::MainWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);

    updatePatientTreeView();
}

void mm::MainWindow::onAddPrescriptionClicked() {
    std::unique_ptr<Dialog> dialog(new AddPrescriptionDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
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
        row[model::Patient::patientTreeModel.birth_date] = patients[i].get_birth_date();
        row[model::Patient::patientTreeModel.birth_place] = patients[i].get_birth_place();
        row[model::Patient::patientTreeModel.address] = patients[i].get_address();
        row[model::Patient::patientTreeModel.risk_factors] = patients[i].get_risk_factors();


        if (i < patients.size() - 1)
            row = *(patientListStore->append()++);
    }
    updatePrescriptionView();
    updatePatientDetailsView();
}

void mm::MainWindow::updatePrescriptionView() {
    Gtk::Box *prescriptionBox;
    Gtk::TreeView *patientTreeView;
    RefBuilder::get_instance().get_widget("prescriptionBox", prescriptionBox);
    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);

    auto sel = patientTreeView->get_selection()->get_selected();
    if (not sel) return;

    for (auto it : prescriptionBox->get_children()) {
        prescriptionBox->remove(*it);
    }

    Glib::ustring patientId = static_cast<Glib::ustring>((*sel)[model::Patient::patientTreeModel.fiscal_code]);
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patientId.c_str());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    auto prescriptions = patient.get_prescriptions();
    for (auto &prescription : prescriptions) {
        std::unique_ptr<mm::view::PrescriptionExpander> tmp(new mm::view::PrescriptionExpander(prescription));
        prescriptionBox->pack_start(*tmp);
        prescriptionsExp.push_back(std::move(tmp));
    }
}

void mm::MainWindow::onSelectedPatient(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *) {
    updatePrescriptionView();
    updatePatientDetailsView();
}

void mm::MainWindow::updatePatientDetailsView() {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::TreeView *patientTreeView;
    Gtk::Label *first_name;
    Gtk::Label *last_name;
    Gtk::Label *fiscal_code;
    Gtk::Label *birth_date;
    Gtk::Label *birth_place;
    Gtk::Label *address;

    refBuilder.get_widget("detailFirstName", first_name);
    refBuilder.get_widget("detailLastName", last_name);
    refBuilder.get_widget("detailFiscalCode", fiscal_code);
    refBuilder.get_widget("detailBirthDate", birth_date);
    refBuilder.get_widget("detailBirthPlace", birth_place);
    refBuilder.get_widget("detailAddress", address);
    refBuilder.get_widget("patientTreeView", patientTreeView);


    auto sel = patientTreeView->get_selection()->get_selected();

    if (not sel) return;

    Glib::ustring patientId = static_cast<Glib::ustring>((*sel)[model::Patient::patientTreeModel.fiscal_code]);
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patientId.c_str());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    first_name->set_label(patient.get_first_name());
    last_name->set_label(patient.get_last_name());
    fiscal_code->set_label(patient.get_fiscal_code());
    birth_date->set_label(patient.get_birth_date());
    birth_place->set_label(patient.get_birth_place());
    address->set_label(patient.get_address());
}

void mm::MainWindow::onRemovePatientClicked() {
    Gtk::Window *mainWindow;
    Gtk::TreeView *patientTreeView;
    model::Patient patient;

    RefBuilder::get_instance().get_widget("mainWindow", mainWindow);
    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);

    auto sel = patientTreeView->get_selection()->get_selected();

    if (not sel) {
        Gtk::MessageDialog info(*mainWindow, "Nessun paziente selezionato", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        info.run();
        return;
    }

    Glib::ustring patientId = static_cast<Glib::ustring>((*sel)[model::Patient::patientTreeModel.fiscal_code]);

    try {
        DBMaster::get_instance().extract_from_db(patient, patientId.c_str());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    Gtk::MessageDialog confirm(*mainWindow,
                               "Conferma di voler eliminare il paziente?",
                               false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);

    confirm.set_secondary_text(
            fmt::format("Conferma di voler rimuovere il paziente:\n{} {} cod. fiscale: {} dal database?",
                        patient.get_first_name(), patient.get_last_name(),
                        patient.get_fiscal_code()));

    auto result = confirm.run();

    if (result == Gtk::RESPONSE_OK) {
        try {
            DBMaster::get_instance().remove_from_db(patient);
        } catch (...) {
            spdlog::get("err")->error("cannot delete patient");
            Gtk::MessageDialog info(*mainWindow, "Impossibile eliminare il pazient", false, Gtk::MESSAGE_INFO,
                                    Gtk::BUTTONS_OK);
            info.run();
            return;
        }

        updatePatientTreeView();
    }
}

void mm::MainWindow::onLogout() {
    next = LOGIN;
    notify();
}

void mm::MainWindow::onAboutClicked() {
    std::unique_ptr<Dialog> dialog(new AboutDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
}

void mm::MainWindow::updateDetailStack(mm::MainWindow::DetailStack page) {
    Gtk::Stack *detail_stack;
    RefBuilder::get_instance().get_widget("detailStack", detail_stack);
    // todo sistemare stack pane. Se premo su due prescrizioni diverse non deve chiudersi
    const Glib::ustring &current = detail_stack->get_visible_child_name();

    if (page == NONE) {
        detail_stack->set_visible(false);
        return;
    }

    if (page == PRESCRIPTION && current != "prescriptionDetail")
        detail_stack->set_visible_child("prescriptionDetail");
    else if (page == DRUG && current != "drugDetail")
        detail_stack->set_visible_child("drugDetail");
    else
        detail_stack->set_visible(!detail_stack->get_visible());
}