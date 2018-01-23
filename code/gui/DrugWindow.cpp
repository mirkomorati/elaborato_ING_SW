//
// Created by Noè Murr on 18/01/2018.
//

#include "DrugWindow.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Doctor.hpp"
#include "../model/Authentication.hpp"

bool mm::DrugWindow::init() {
    initHandler();
    initTreeView();
    initDrugFilter();
    initQuantityFilter();
    return true;
}

mm::WindowName mm::DrugWindow::getName() const {
    return DRUG;
}

mm::WindowName mm::DrugWindow::getNextWindow() const {
    return next;
}

mm::DrugWindow::DrugWindow() : next(MAIN), drugListStore(Gtk::ListStore::create(model::Drug::drugTreeModel)) {}

void mm::DrugWindow::update() {

}

void mm::DrugWindow::initHandler() {
    Gtk::EventBox *openFilterEventBox, *closedFilterEventBox;
    Gtk::TreeView *drugTreeView;
    auto refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("drugOpenFilterEventBox", openFilterEventBox);
    refBuilder.get_widget("drugCloseFilterEventBox", closedFilterEventBox);
    refBuilder.get_widget("drugTreeView", drugTreeView);

    openFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);
    closedFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);

    drugTreeView->signal_row_activated().connect(sigc::mem_fun(this, &mm::DrugWindow::onSelectedDrug));
    openFilterEventBox->signal_button_press_event().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterClose));
    closedFilterEventBox->signal_button_press_event().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterOpened));
}

void mm::DrugWindow::initTreeView() {
    Gtk::TreeView *drugTreeView;

    RefBuilder::get_instance().get_widget("drugTreeView", drugTreeView);

    drugTreeView->append_column("Nome", model::Drug::drugTreeModel.name);
    drugTreeView->append_column("Forma Farmaceutica", model::Drug::drugTreeModel.pharmaceutical_form);
    drugTreeView->append_column("Principi Attivi", model::Drug::drugTreeModel.active_principles);
    drugTreeView->set_model(drugListStore);

    for (int i = 0; i <= 2; i++) {
        drugTreeView->get_column(i)->set_min_width(100);
        drugTreeView->get_column(i)->set_resizable(true);
        drugTreeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
        drugTreeView->get_column(i)->set_sort_column(i);
        drugTreeView->get_column(i)->set_sort_order(Gtk::SortType::SORT_ASCENDING);
        drugTreeView->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        drugTreeView->get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    updateDrugTreeView();
}

void mm::DrugWindow::updateDrugTreeView() {
    model::Drug drug;
    std::vector<model::Drug> drugs;
    std::vector<std::map<std::string, mm::Serialized>> rows;
    try {
        rows = DBMaster::get_instance().get_rows(drug.get_table_name());
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the drugs from the db...");
    }

    for (auto &row : rows) {
        model::Drug tmp;
        tmp.unserialize(row);
        drugs.push_back(tmp);
    }

    drugListStore->clear();

    auto row = *drugListStore->append();

    for (size_t i = 0; i < drugs.size(); i++) {
        row[model::Drug::drugTreeModel.name] = drugs[i].get_name();
        row[model::Drug::drugTreeModel.pharmaceutical_form] = drugs[i].get_pharmaceutical_form();
        row[model::Drug::drugTreeModel.active_principles] = drugs[i].get_active_principles_as_string();

        if (i < drugs.size() - 1)
            row = *(drugListStore->append()++);
    }
}

void mm::DrugWindow::onSelectedDrug(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *) {
    updatePatientView();
    updateDrugDetailsView();
}

void mm::DrugWindow::updatePatientView() {
    Gtk::ListBox *patientList;
    Gtk::TreeView *drugTreeView;
    RefBuilder::get_instance().get_widget("patientListBox", patientList);
    RefBuilder::get_instance().get_widget("drugTreeView", drugTreeView);

    patientExp.clear();

    for (auto it : patientList->get_children())
        patientList->remove(*it);

    auto sel = drugTreeView->get_selection()->get_selected();
    if (not sel) return;

    Glib::ustring nameID = static_cast<Glib::ustring>((*sel)[model::Drug::drugTreeModel.name]);
    Glib::ustring pharmaceuticalFormID = static_cast<Glib::ustring>((*sel)[model::Drug::drugTreeModel.pharmaceutical_form]);

    model::Drug drug;
    model::Doctor doctor;

    try {
        DBMaster::get_instance().extract_from_db(drug, {nameID.c_str(), pharmaceuticalFormID.c_str()});
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the drug from the db...");
    }

    try {
        DBMaster::get_instance().extract_from_db(doctor, mm::model::authentication::Login::get_instance().regional_id);
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the doctor from the db...");
    }

    for (const auto &patient : doctor.get_patients()) {
        bool flag = false;
        for (const auto &p : patient.get_prescriptions()) {
            const auto &drugs = p.get_drugs();
            if (std::find(drugs.begin(), drugs.end(), drug) != drugs.end()) {
                flag = true;
                break;
            }
        }

        if (flag) {
            std::unique_ptr<view::PatientExpander> exp(new view::PatientExpander(patient, drug));
            patientList->append(*exp);
            patientExp.push_back(std::move(exp));
        }
    }


}

void mm::DrugWindow::updateDrugDetailsView() {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::TreeView *drugTreeView;
    Gtk::Label *name;
    Gtk::Label *pharmaceutical_form;
    Gtk::Label *ATC_classification;
    Gtk::Label *contraindications;
    Gtk::Label *active_principles;
    Gtk::Label *price;

    refBuilder.get_widget("drugDetailName", name);
    refBuilder.get_widget("drugDetailPharmaceuticalForm", pharmaceutical_form);
    refBuilder.get_widget("drugDetailATCClassification", ATC_classification);
    refBuilder.get_widget("drugDetailContraindications", contraindications);
    refBuilder.get_widget("drugDetailActivePrinciples", active_principles);
    refBuilder.get_widget("drugDetailPrice", price);
    refBuilder.get_widget("drugTreeView", drugTreeView);


    auto sel = drugTreeView->get_selection()->get_selected();

    if (not sel) return;

    Glib::ustring nameID = static_cast<Glib::ustring>((*sel)[model::Drug::drugTreeModel.name]);
    Glib::ustring pharmaceuticalFormID = static_cast<Glib::ustring>((*sel)[model::Drug::drugTreeModel.pharmaceutical_form]);

    model::Drug drug;

    try {
        DBMaster::get_instance().extract_from_db(drug, {nameID.c_str(), pharmaceuticalFormID.c_str()});
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get the Patient from the db...");
    }

    name->set_label(drug.get_name());
    pharmaceutical_form->set_label(drug.get_pharmaceutical_form());
    ATC_classification->set_label(drug.get_ATC_classification());
    contraindications->set_label(drug.get_contraindications_as_string());
    active_principles->set_label(drug.get_active_principles_as_string());
    price->set_label(Glib::ustring::format(drug.get_price()));
}

void mm::DrugWindow::initDrugFilter() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *monthMonthCombo, *monthYearCombo;

    refBuilder.get_widget("drugYearFilterComboBox", yearCombo);
    refBuilder.get_widget("drugMonthFilterMonthComboBox", monthMonthCombo);
    refBuilder.get_widget("drugMonthFilterYearComboBox", monthYearCombo);

    for (int i = util::Date::get_current_year(); i >= 1920; i--) {
        yearCombo->append(Glib::ustring::format(i));
        monthYearCombo->append(Glib::ustring::format(i));
    }
    for (int i = 1; i <= 12; i++) {
        monthMonthCombo->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    }

    yearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
    monthYearCombo->set_active_text(Glib::ustring::format(util::Date::get_current_year()));

    monthMonthCombo->set_active_text(Glib::ustring::format("01"));
}

void mm::DrugWindow::initQuantityFilter() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *semesterMonthCombo, *semesterYearCombo;
    Gtk::ComboBoxText *quarterMonthCombo, *quarterYearCombo;
    Gtk::ComboBoxText *monthMonthCombo, *monthYearCombo;

    refBuilder.get_widget("quantityYearFilterComboBox", yearCombo);
    refBuilder.get_widget("quantitySemesterFilterMonthComboBox", semesterMonthCombo);
    refBuilder.get_widget("quantitySemesterFilterYearComboBox", semesterYearCombo);
    refBuilder.get_widget("quantityQuarterFilterMonthComboBox", quarterMonthCombo);
    refBuilder.get_widget("quantityQuarterFilterYearComboBox", quarterYearCombo);
    refBuilder.get_widget("quantityMonthFilterMonthComboBox", monthMonthCombo);
    refBuilder.get_widget("quantityMonthFilterYearComboBox", monthYearCombo);

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

bool mm::DrugWindow::onFilterClose(GdkEventButton *buttonEvent) {
    if (buttonEvent->button != 1) return false;
    Gtk::Frame *filterFrame;
    Gtk::Grid *closedFilterGrid;

    RefBuilder::get_instance().get_widget("drugOpenFilters", filterFrame);
    RefBuilder::get_instance().get_widget("drugClosedFilters", closedFilterGrid);

    filterFrame->set_visible(false);
    closedFilterGrid->set_visible(true);

    return true;
}

bool mm::DrugWindow::onFilterOpened(GdkEventButton *buttonEvent) {
    if (buttonEvent->button != 1) return false;
    Gtk::Frame *filterFrame;
    Gtk::Grid *closedFilterGrid;

    RefBuilder::get_instance().get_widget("drugOpenFilters", filterFrame);
    RefBuilder::get_instance().get_widget("drugClosedFilters", closedFilterGrid);

    filterFrame->set_visible(true);
    closedFilterGrid->set_visible(false);

    return true;
}

