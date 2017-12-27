//
// Created by Noè Murr on 29/11/2017.
//

#include <gtkmm/button.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "PatientWindow.hpp"
#include "RefBuilder.hpp"
#include "AddPatientDialog.hpp"
#include "../model/Doctor.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"
#include "AddPrescriptionDialog.hpp"
#include "AboutDialog.hpp"

mm::PatientWindow::PatientWindow() :
        next(MAIN),
        patientListStore(Gtk::ListStore::create(model::Patient::patientTreeModel)),
        filterOn(false),
        filterStartDate(util::Date::get_current_date()),
        filterEndDate(util::Date::get_current_date()),
        customFilterFromDateController("customFilterFromDay", "customFilterFromMonth", "customFilterFromYear"),
        customFilterToDateController("customFilterToDay", "customFilterToMonth", "customFilterToYear") {}

void mm::PatientWindow::initHandlers() {
    auto refBuilder = RefBuilder::get_instance();

    Gtk::TreeView *patientTreeView;
    Gtk::ToolButton *add_patient_button;
    Gtk::ToolButton *add_prescription_button;
    Gtk::ToolButton *remove_patient_button;
    Gtk::ToolButton *remove_prescription_button;
    Gtk::MenuItem *logoutMenuItem;
    Gtk::ImageMenuItem *aboutMenuItem;
    Gtk::Switch *filterSwitch;
    Gtk::RadioButton *year, *semester, *quarter, *month, *custom;
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *semesterYearCombo, *semesterMonthCombo;
    Gtk::ComboBoxText *quarterYearCombo, *quarterMonthCombo;
    Gtk::ComboBoxText *monthYearCombo, *monthMonthCombo;
    Gtk::ComboBoxText *customFromDayCombo, *customFromMonthCombo, *customFromYearCombo;
    Gtk::ComboBoxText *customToDayCombo, *customToMonthCombo, *customToYearCombo;

    refBuilder.get_widget("patientTreeView", patientTreeView);
    refBuilder.get_widget("addPatient", add_patient_button);
    refBuilder.get_widget("addPrescription", add_prescription_button);
    refBuilder.get_widget("removePatient", remove_patient_button);
    refBuilder.get_widget("removePrescription", remove_prescription_button);
    refBuilder.get_widget("logoutMenuItem", logoutMenuItem);
    refBuilder.get_widget("aboutMenuItem", aboutMenuItem);
    refBuilder.get_widget("filterSwitch", filterSwitch);
    refBuilder.get_widget("yearFilterRadioButton", year);
    refBuilder.get_widget("semesterFilterRadioButton", semester);
    refBuilder.get_widget("quarterFilterRadioButton", quarter);
    refBuilder.get_widget("monthFilterRadioButton", month);
    refBuilder.get_widget("customFilterRadioButton", custom);
    refBuilder.get_widget("yearFilterComboBox", yearCombo);
    refBuilder.get_widget("semesterFilterYearComboBox", semesterYearCombo);
    refBuilder.get_widget("semesterFilterMonthComboBox", semesterMonthCombo);
    refBuilder.get_widget("quarterFilterYearComboBox", quarterYearCombo);
    refBuilder.get_widget("quarterFilterMonthComboBox", quarterMonthCombo);
    refBuilder.get_widget("monthFilterYearComboBox", monthYearCombo);
    refBuilder.get_widget("monthFilterMonthComboBox", monthMonthCombo);
    refBuilder.get_widget("customFilterFromDay", customFromDayCombo);
    refBuilder.get_widget("customFilterFromMonth", customFromMonthCombo);
    refBuilder.get_widget("customFilterFromYear", customFromYearCombo);
    refBuilder.get_widget("customFilterToDay", customToDayCombo);
    refBuilder.get_widget("customFilterToMonth", customToMonthCombo);
    refBuilder.get_widget("customFilterToYear", customToYearCombo);


    add_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onAddPatientClicked));
    add_prescription_button->signal_clicked().connect(
            sigc::mem_fun(this, &mm::PatientWindow::onAddPrescriptionClicked));
    patientTreeView->signal_row_activated().connect(sigc::mem_fun(this, &mm::PatientWindow::onSelectedPatient));
    remove_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onRemovePatientClicked));
    remove_prescription_button->signal_clicked().connect(
            sigc::mem_fun(this, &mm::PatientWindow::onRemovePrescriptionClicked));

    //-------------------Filter signals-------------------//
    filterSwitch->property_active().signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onSwitchActivate));

    year->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterYearChanged));
    yearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterYearChanged));

    semester->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterSemesterChanged));
    semesterYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterSemesterChanged));
    semesterMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterSemesterChanged));

    quarter->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterQuarterChanged));
    quarterYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterQuarterChanged));
    quarterMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterQuarterChanged));

    month->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterMonthChanged));
    monthYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterMonthChanged));
    monthMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterMonthChanged));

    custom->signal_clicked().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customFromDayCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customFromMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customFromYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customToDayCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customToMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
    customToYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::PatientWindow::onFilterCustomChanged));
}

void mm::PatientWindow::initTreeView() {
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

bool mm::PatientWindow::init() {

    initHandlers();
    initTreeView();
    initFilters();

    return true;
}

mm::WindowName mm::PatientWindow::getName() const {
    return PATIENT;
}

mm::WindowName mm::PatientWindow::getNextWindow() const {
    return next;
}

void mm::PatientWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);

    updatePatientTreeView();
}

void mm::PatientWindow::onAddPrescriptionClicked() {
    std::unique_ptr<Dialog> dialog(new AddPrescriptionDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
}

void mm::PatientWindow::onAddPatientClicked() {
    std::unique_ptr<Dialog> dialog(new AddPatientDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
}

void mm::PatientWindow::updatePatientTreeView() {
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

void mm::PatientWindow::updatePrescriptionView() {
    Gtk::ListBox *prescriptionList;
    Gtk::TreeView *patientTreeView;
    RefBuilder::get_instance().get_widget("prescriptionList", prescriptionList);
    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);

    auto sel = patientTreeView->get_selection()->get_selected();
    if (not sel) return;

    for (auto it : prescriptionList->get_children()) {
        prescriptionList->remove(*it);
    }

    Glib::ustring patientId = static_cast<Glib::ustring>((*sel)[model::Patient::patientTreeModel.fiscal_code]);
    model::Patient patient;

    try {
        DBMaster::get_instance().extract_from_db(patient, patientId.c_str());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    auto prescriptions = patient.get_prescriptions();

    if (filterOn) {
        auto it = prescriptions.begin();
        while (it != prescriptions.end()) {
            util::Date date(it->get_issue_date());
            if (date < filterStartDate or date >= filterEndDate) {
                prescriptions.erase(it);
                it = prescriptions.begin();
            } else
                ++it;
        }
    }

    int i = 0;
    for (auto &prescription : prescriptions) {
        std::unique_ptr<mm::view::PrescriptionExpander> tmp(new mm::view::PrescriptionExpander(prescription));
        prescriptionList->append(*tmp);
        prescriptionsExp.push_back(std::move(tmp));
        ++i;
    }
}

void mm::PatientWindow::onSelectedPatient(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *) {
    updatePrescriptionView();
    updatePatientDetailsView();
}

void mm::PatientWindow::updatePatientDetailsView() {
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

void mm::PatientWindow::onRemovePatientClicked() {
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
            Gtk::MessageDialog info(*mainWindow, "Impossibile eliminare il paziente", false, Gtk::MESSAGE_INFO,
                                    Gtk::BUTTONS_OK);
            info.run();
            return;
        }

        updatePatientTreeView();
    }
}

mm::PatientWindow::~PatientWindow() {
    Gtk::TreeView *patientTreeView;
    Gtk::ListBox *prescriptionList;

    RefBuilder::get_instance().get_widget("patientTreeView", patientTreeView);
    RefBuilder::get_instance().get_widget("prescriptionList", prescriptionList);

    for (auto it : prescriptionList->get_children()) {
        prescriptionList->remove(*it);
    }

    patientTreeView->remove_all_columns();
}

void mm::PatientWindow::onSwitchActivate() {
    Gtk::Grid *filterGrid;
    Gtk::Switch *filterSwitch;
    RefBuilder::get_instance().get_widget("filterGrid", filterGrid);
    RefBuilder::get_instance().get_widget("filterSwitch", filterSwitch);

    filterGrid->set_sensitive(filterSwitch->get_active());
    filterOn = filterSwitch->get_active();
    onFilterYearChanged();
}

void mm::PatientWindow::initFilters() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *semesterMonthCombo, *semesterYearCombo;
    Gtk::ComboBoxText *quarterMonthCombo, *quarterYearCombo;
    Gtk::ComboBoxText *monthMonthCombo, *monthYearCombo;

    refBuilder.get_widget("yearFilterComboBox", yearCombo);
    refBuilder.get_widget("semesterFilterMonthComboBox", semesterMonthCombo);
    refBuilder.get_widget("semesterFilterYearComboBox", semesterYearCombo);
    refBuilder.get_widget("quarterFilterMonthComboBox", quarterMonthCombo);
    refBuilder.get_widget("quarterFilterYearComboBox", quarterYearCombo);
    refBuilder.get_widget("monthFilterMonthComboBox", monthMonthCombo);
    refBuilder.get_widget("monthFilterYearComboBox", monthYearCombo);

    for (int i = util::Date::get_current_year(); i >= 1920; i--) {
        yearCombo->append(Glib::ustring::format(i));
        semesterYearCombo->append(Glib::ustring::format(i));
        quarterYearCombo->append(Glib::ustring::format(i));
        monthYearCombo->append(Glib::ustring::format(i));
    }
    for (int i = 1; i <= 12; i++) {
        semesterMonthCombo->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
        quarterMonthCombo->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
        monthMonthCombo->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    }

    yearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
    semesterYearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
    quarterYearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
    monthYearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));

    semesterMonthCombo->set_active_text(Glib::ustring::format("01"));
    quarterMonthCombo->set_active_text(Glib::ustring::format("01"));
    monthMonthCombo->set_active_text(Glib::ustring::format("01"));
}

void mm::PatientWindow::onFilterYearChanged() {
    if (filterOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *year;
        Gtk::ComboBoxText *yearCombo;

        refBuilder.get_widget("yearFilterRadioButton", year);
        refBuilder.get_widget("yearFilterComboBox", yearCombo);

        yearCombo->set_visible(year->get_active());

        if (year->get_active()) {
            filterStartDate.set_from_str(fmt::format("01/01/{}", yearCombo->get_active_text().c_str()));
            filterEndDate = filterStartDate;
            filterEndDate.add_years(1);

            spdlog::get("out")->info("Filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePrescriptionView();
}

void mm::PatientWindow::onFilterSemesterChanged() {
    if (filterOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *semester;
        Gtk::ComboBoxText *yearCombo, *monthCombo;
        Gtk::Grid *semesterFilterGrid;

        refBuilder.get_widget("semesterFilterRadioButton", semester);
        refBuilder.get_widget("semesterFilterYearComboBox", yearCombo);
        refBuilder.get_widget("semesterFilterMonthComboBox", monthCombo);
        refBuilder.get_widget("semesterFilterGrid", semesterFilterGrid);

        semesterFilterGrid->set_visible(semester->get_active());

        if (semester->get_active()) {
            filterStartDate.set_from_str(fmt::format("01/{}/{}",
                                                     monthCombo->get_active_text().c_str(),
                                                     yearCombo->get_active_text().c_str()));
            filterEndDate = filterStartDate;
            filterEndDate.add_months(6);

            spdlog::get("out")->info("Filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePrescriptionView();
}

void mm::PatientWindow::onFilterQuarterChanged() {
    if (filterOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *quarter;
        Gtk::ComboBoxText *yearCombo, *monthCombo;
        Gtk::Grid *quarterFilterGrid;

        refBuilder.get_widget("quarterFilterRadioButton", quarter);
        refBuilder.get_widget("quarterFilterYearComboBox", yearCombo);
        refBuilder.get_widget("quarterFilterMonthComboBox", monthCombo);
        refBuilder.get_widget("quarterFilterGrid", quarterFilterGrid);

        quarterFilterGrid->set_visible(quarter->get_active());

        if (quarter->get_active()) {
            filterStartDate.set_from_str(fmt::format("01/{}/{}",
                                                     monthCombo->get_active_text().c_str(),
                                                     yearCombo->get_active_text().c_str()));
            filterEndDate = filterStartDate;
            filterEndDate.add_months(3);

            spdlog::get("out")->info("Filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePrescriptionView();
}

void mm::PatientWindow::onFilterMonthChanged() {
    if (filterOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *month;
        Gtk::ComboBoxText *yearCombo, *monthCombo;
        Gtk::Grid *filterGrid;

        refBuilder.get_widget("monthFilterRadioButton", month);
        refBuilder.get_widget("monthFilterYearComboBox", yearCombo);
        refBuilder.get_widget("monthFilterMonthComboBox", monthCombo);
        refBuilder.get_widget("monthFilterGrid", filterGrid);

        filterGrid->set_visible(month->get_active());

        if (month->get_active()) {
            filterStartDate.set_from_str(fmt::format("01/{}/{}",
                                                     monthCombo->get_active_text().c_str(),
                                                     yearCombo->get_active_text().c_str()));
            filterEndDate = filterStartDate;
            filterEndDate.add_months(1);

            spdlog::get("out")->info("Filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePrescriptionView();
}

void mm::PatientWindow::onFilterCustomChanged() {
    if (filterOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::Grid *filterGrid;
        Gtk::RadioButton *custom;

        refBuilder.get_widget("customFilterRadioButton", custom);
        refBuilder.get_widget("customFilterGrid", filterGrid);

        filterGrid->set_visible(custom->get_active());

        if (custom->get_active()) {
            filterStartDate = customFilterFromDateController.getDate();
            filterEndDate = customFilterToDateController.getDate();

            spdlog::get("out")->info("Filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePrescriptionView();
}

void mm::PatientWindow::onRemovePrescriptionClicked() {
    Gtk::Window *mainWindow;
    Gtk::ListBox *listBox;
    model::Prescription prescription;

    RefBuilder::get_instance().get_widget("mainWindow", mainWindow);
    RefBuilder::get_instance().get_widget("prescriptionList", listBox);

    auto sel = listBox->get_selected_row();

    if (not sel) {
        Gtk::MessageDialog info(*mainWindow, "Nessuna prescrizione selezionata", false, Gtk::MESSAGE_INFO,
                                Gtk::BUTTONS_OK);
        info.run();
        return;
    }

    view::PrescriptionExpander *pExpander;
    if (not(pExpander = dynamic_cast<view::PrescriptionExpander *>(sel->get_child()))) {

        throw logic_error("header of Prescription list box is not a prescriptionExpander obj");
    }

    Glib::ustring prescriptionID = static_cast<Glib::ustring>(std::to_string(pExpander->getID()));

    try {
        DBMaster::get_instance().extract_from_db(prescription, prescriptionID.c_str());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the prescription from the db...");
    }

    Gtk::MessageDialog confirm(*mainWindow,
                               "Confermi di voler eliminare la prescrizione?",
                               false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);

    confirm.set_secondary_text(
            fmt::format("Confermi di voler rimuovere la prescrizione con id: {} dal database?",
                        prescription.get_prescription_id()));

    auto result = confirm.run();

    if (result == Gtk::RESPONSE_OK) {
        try {
            DBMaster::get_instance().remove_from_db(prescription);
        } catch (...) {
            spdlog::get("err")->error("cannot delete prescription");
            Gtk::MessageDialog info(*mainWindow, "Impossibile eliminare la prescrizione", false, Gtk::MESSAGE_INFO,
                                    Gtk::BUTTONS_OK);
            info.run();
            return;
        }

        updatePrescriptionView();
    }
}

