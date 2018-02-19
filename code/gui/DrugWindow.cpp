//
// Created by Noè Murr on 18/01/2018.
//

#include <spdlog/spdlog.h>
#include "DrugWindow.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Doctor.hpp"
#include "../model/Authentication.hpp"

bool mm::DrugWindow::init() {
    initTreeView();
    initDrugFilter();
    initQuantityFilter();
    initHandlers();
    return true;
}

mm::WindowName mm::DrugWindow::getName() const {
    return DRUG;
}

mm::WindowName mm::DrugWindow::getNextWindow() const {
    return next;
}

mm::DrugWindow::DrugWindow() : next(MAIN),
                               drugListStore(Gtk::ListStore::create(model::Drug::drugTreeModel)),
                               filterStartDate(util::Date::get_current_date()),
                               filterEndDate(util::Date::get_current_date()),
                               quantityStartDate(util::Date::get_current_date()),
                               quantityEndDate(util::Date::get_current_date()),
                               filterDrugOn(false), filterQuantityOn(false) {}

void mm::DrugWindow::update() {

}

void mm::DrugWindow::initHandlers() {
    Gtk::EventBox *openFilterEventBox, *closedFilterEventBox;
    Gtk::Switch *filterSwitch;
    Gtk::TreeView *drugTreeView;
    Gtk::RadioButton *year, *month, *qYear, *qSemester, *qQuarter, *qMonth;
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *monthYearCombo, *monthMonthCombo;
    Gtk::ComboBoxText *qYearCombo;
    Gtk::ComboBoxText *qSemesterYearCombo, *qSemesterMonthCombo;
    Gtk::ComboBoxText *qQuarterYearCombo, *qQuarterMonthCombo;
    Gtk::ComboBoxText *qMonthYearCombo, *qMonthMonthCombo;


    auto refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("drugOpenFilterEventBox", openFilterEventBox);
    refBuilder.get_widget("drugCloseFilterEventBox", closedFilterEventBox);
    refBuilder.get_widget("drugFilterSwitch", filterSwitch);
    refBuilder.get_widget("drugTreeView", drugTreeView);
    refBuilder.get_widget("drugYearFilterRadioButton", year);
    refBuilder.get_widget("drugMonthFilterRadioButton", month);
    refBuilder.get_widget("quantityYearRadioButton", qYear);
    refBuilder.get_widget("quantitySemesterRadioButton", qSemester);
    refBuilder.get_widget("quantityQuarterRadioButton", qQuarter);
    refBuilder.get_widget("quantityMonthRadioButton", qMonth);
    refBuilder.get_widget("drugYearFilterComboBox", yearCombo);
    refBuilder.get_widget("drugMonthFilterYearComboBox", monthYearCombo);
    refBuilder.get_widget("drugMonthFilterMonthComboBox", monthMonthCombo);
    refBuilder.get_widget("quantityYearFilterComboBox", qYearCombo);
    refBuilder.get_widget("quantitySemesterFilterYearComboBox", qSemesterYearCombo);
    refBuilder.get_widget("quantitySemesterFilterMonthComboBox", qSemesterMonthCombo);
    refBuilder.get_widget("quantityQuarterFilterYearComboBox", qQuarterYearCombo);
    refBuilder.get_widget("quantityQuarterFilterMonthComboBox", qQuarterMonthCombo);
    refBuilder.get_widget("quantityMonthFilterYearComboBox", qMonthYearCombo);
    refBuilder.get_widget("quantityMonthFilterMonthComboBox", qMonthMonthCombo);

    openFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);
    closedFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);

    year->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterYearChanged));
    yearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterYearChanged));

    month->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterMonthChanged));
    monthYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterMonthChanged));
    monthMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterMonthChanged));

    qYear->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityYearChanged));
    qYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityYearChanged));

    qSemester->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantitySemesterChanged));
    qSemesterYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantitySemesterChanged));
    qSemesterMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantitySemesterChanged));

    qQuarter->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityQuarterChanged));
    qQuarterYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityQuarterChanged));
    qQuarterMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityQuarterChanged));

    qMonth->signal_clicked().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityMonthChanged));
    qMonthYearCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityMonthChanged));
    qMonthMonthCombo->signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onQuantityMonthChanged));


    filterSwitch->property_active().signal_changed().connect(sigc::mem_fun(this, &mm::DrugWindow::onSwitchActivate));
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
        drugTreeView->get_column(i)->set_min_width(120);
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
    updateTotalDrug();
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
            if (filterDrugOn) {
                const util::Date &date = util::Date(p.get_issue_date());
                if (date < filterStartDate or date >= filterEndDate) {
                    continue;
                }
            }
            const auto &drugs = p.get_drugs();
            if (std::find(drugs.begin(), drugs.end(), drug) != drugs.end()) {
                flag = true;
                break;
            }
        }

        if (flag) {
            std::unique_ptr<view::PatientExpander> exp(
                    new view::PatientExpander(patient, drug, filterStartDate, filterEndDate));
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

void mm::DrugWindow::onSwitchActivate() {
    Gtk::Grid *filterGrid;
    Gtk::Switch *filterSwitch;
    RefBuilder::get_instance().get_widget("drugFilterGrid", filterGrid);
    RefBuilder::get_instance().get_widget("drugFilterSwitch", filterSwitch);

    filterGrid->set_sensitive(filterSwitch->get_active());
    filterDrugOn = filterSwitch->get_active();
    onFilterYearChanged();
}

void mm::DrugWindow::onFilterYearChanged() {
    if (filterDrugOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *year;
        Gtk::ComboBoxText *yearCombo;

        refBuilder.get_widget("drugYearFilterRadioButton", year);
        refBuilder.get_widget("drugYearFilterComboBox", yearCombo);

        yearCombo->set_visible(year->get_active());

        if (year->get_active()) {
            filterStartDate.set_from_str(fmt::format("01/01/{}", yearCombo->get_active_text().c_str()));
            filterEndDate = filterStartDate;
            filterEndDate.add_years(1);

            spdlog::get("out")->info("Drug filter on. start date: {}. end date: {}.",
                                     filterStartDate.get_as_text(), filterEndDate.get_as_text());
        }
    }

    updatePatientView();
}

void mm::DrugWindow::onFilterMonthChanged() {
    if (filterDrugOn) {
        auto refBuilder = RefBuilder::get_instance();
        Gtk::RadioButton *month;
        Gtk::ComboBoxText *yearCombo, *monthCombo;
        Gtk::Grid *filterGrid;

        refBuilder.get_widget("drugMonthFilterRadioButton", month);
        refBuilder.get_widget("drugMonthFilterYearComboBox", yearCombo);
        refBuilder.get_widget("drugMonthFilterMonthComboBox", monthCombo);
        refBuilder.get_widget("drugMonthFilterGrid", filterGrid);

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

    updatePatientView();
}

void mm::DrugWindow::onQuantityYearChanged() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::RadioButton *year;
    Gtk::ComboBoxText *yearCombo;

    refBuilder.get_widget("quantityYearRadioButton", year);
    refBuilder.get_widget("quantityYearFilterComboBox", yearCombo);

    if (year->get_active()) {
        quantityStartDate.set_from_str(fmt::format("01/01/{}", yearCombo->get_active_text().c_str()));
        quantityEndDate = quantityStartDate;
        quantityEndDate.add_years(1);

        spdlog::get("out")->info("Drug quantity count. start date: {}. end date: {}.",
                                 quantityStartDate.get_as_text(), quantityEndDate.get_as_text());
    }

    updateTotalDrug();
}

void mm::DrugWindow::onQuantitySemesterChanged() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::RadioButton *semester;
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *monthCombo;

    refBuilder.get_widget("quantitySemesterRadioButton", semester);
    refBuilder.get_widget("quantitySemesterFilterYearComboBox", yearCombo);
    refBuilder.get_widget("quantitySemesterFilterMonthComboBox", monthCombo);

    if (semester->get_active()) {
        quantityStartDate.set_from_str(fmt::format("01/{}/{}",
                                                   monthCombo->get_active_text().c_str(),
                                                   yearCombo->get_active_text().c_str()));
        quantityEndDate = quantityStartDate;
        quantityEndDate.add_months(6);

        spdlog::get("out")->info("Drug quantity count. start date: {}. end date: {}.",
                                 quantityStartDate.get_as_text(), quantityEndDate.get_as_text());
    }

    updateTotalDrug();
}

void mm::DrugWindow::onQuantityQuarterChanged() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::RadioButton *quarter;
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *monthCombo;

    refBuilder.get_widget("quantityQuarterRadioButton", quarter);
    refBuilder.get_widget("quantityQuarterFilterYearComboBox", yearCombo);
    refBuilder.get_widget("quantityQuarterFilterMonthComboBox", monthCombo);

    if (quarter->get_active()) {
        quantityStartDate.set_from_str(fmt::format("01/{}/{}",
                                                   monthCombo->get_active_text().c_str(),
                                                   yearCombo->get_active_text().c_str()));
        quantityEndDate = quantityStartDate;
        quantityEndDate.add_months(3);

        spdlog::get("out")->info("Drug quantity count. start date: {}. end date: {}.",
                                 quantityStartDate.get_as_text(), quantityEndDate.get_as_text());
    }

    updateTotalDrug();
}

void mm::DrugWindow::onQuantityMonthChanged() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::RadioButton *month;
    Gtk::ComboBoxText *yearCombo;
    Gtk::ComboBoxText *monthCombo;

    refBuilder.get_widget("quantityMonthRadioButton", month);
    refBuilder.get_widget("quantityMonthFilterYearComboBox", yearCombo);
    refBuilder.get_widget("quantityMonthFilterMonthComboBox", monthCombo);

    if (month->get_active()) {
        quantityStartDate.set_from_str(fmt::format("01/{}/{}",
                                                   monthCombo->get_active_text().c_str(),
                                                   yearCombo->get_active_text().c_str()));
        quantityEndDate = quantityStartDate;
        quantityEndDate.add_months(1);

        spdlog::get("out")->info("Drug quantity count. start date: {}. end date: {}.",
                                 quantityStartDate.get_as_text(), quantityEndDate.get_as_text());
    }

    updateTotalDrug();
}

void mm::DrugWindow::updateTotalDrug() {
    auto refBuilder = RefBuilder::get_instance();

    Gtk::Label *quantity;
    Gtk::TreeView *drugTreeView;

    refBuilder.get_widget("quantityTotalLabel", quantity);
    RefBuilder::get_instance().get_widget("drugTreeView", drugTreeView);

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

    int counter = 0;

    for (const auto &patient : doctor.get_patients()) {
        for (const auto &p : patient.get_prescriptions()) {
            const util::Date &date = util::Date(p.get_issue_date());
            if (date < quantityStartDate or date >= quantityEndDate) {
                continue;
            }
            for (const auto &d : p.get_drugs()) {
                if (d == drug) {
                    counter++;
                }
            }
        }
    }

    quantity->set_text(Glib::ustring::format(" ", counter));
}