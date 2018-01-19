//
// Created by Noè Murr on 18/01/2018.
//

#include "DrugWindow.hpp"
#include "RefBuilder.hpp"

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
    auto refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("drugOpenFilterEventBox", openFilterEventBox);
    refBuilder.get_widget("drugCloseFilterEventBox", closedFilterEventBox);

    openFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);
    closedFilterEventBox->set_events(Gdk::BUTTON_PRESS_MASK);

    openFilterEventBox->signal_button_press_event().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterClose));
    closedFilterEventBox->signal_button_press_event().connect(sigc::mem_fun(this, &mm::DrugWindow::onFilterOpened));
}

void mm::DrugWindow::initTreeView() {

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
