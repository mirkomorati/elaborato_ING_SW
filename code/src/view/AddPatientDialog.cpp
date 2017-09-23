//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/view/AddPatientDialog.hpp"

mm::view::AddPatientDialog::AddPatientDialog() : view::Dialog("addPatientDialog") {
    auto refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addFirstName", first_name);
    refBuilder.get_widget("addLastName", last_name);
    refBuilder.get_widget("addFiscalCode", fiscal_code);
    refBuilder.get_widget("addHealthCode", health_code);
    refBuilder.get_widget("addBirthDateDay", combo_day);
    refBuilder.get_widget("addBirthDateMonth", combo_month);
    refBuilder.get_widget("addBirthDateYear", combo_year);
    refBuilder.get_widget("addBirthCity", birth_city);
    refBuilder.get_widget("addBirthCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);
    this->reset_view();
}

void mm::view::AddPatientDialog::set_ok_handler(controller::Dialog *controller,
                                                void (controller::Dialog::*handler)(void)) {
    RefBuilder::get_instance().get_widget("addPatientOk", ok_button);
    c_ok = ok_button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::AddPatientDialog::set_cancel_handler(controller::Dialog *controller,
                                                    void (controller::Dialog::*handler)(void)) {
    RefBuilder::get_instance().get_widget("addPatientCancel", cancel_button);
    c_cancel = cancel_button->signal_clicked().connect(sigc::mem_fun(controller, handler));

}

void mm::view::AddPatientDialog::set_select_date_handler(mm::controller::AddPatientDialog *controller,
                                                         void (controller::AddPatientDialog::*handler)(void)) {
    connections.push_back(combo_day->signal_changed().connect(sigc::mem_fun(controller, handler)));
    connections.push_back(combo_month->signal_changed().connect(sigc::mem_fun(controller, handler)));
    connections.push_back(combo_year->signal_changed().connect(sigc::mem_fun(controller, handler)));
}

mm::view::AddPatientDialog::~AddPatientDialog() {
    for (auto &connection : connections)
        if (not connection.empty()) connection.disconnect();
}

void mm::view::AddPatientDialog::set_add_birth_date(mm::util::Date date) {
    combo_day->set_active_text(Glib::ustring::format(date.day));
    combo_month->set_active_text(Glib::ustring(date.month < 10 ? "0" : "").append(Glib::ustring::format(date.month)));
    combo_year->set_active_text(Glib::ustring::format(date.year));
}

void mm::view::AddPatientDialog::reset_view() {
    for (int i = 1; i <= 31; i++)
        combo_day->append(Glib::ustring::format(i));
    for (int i = 1; i <= 12; i++)
        combo_month->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    for (int i = util::Date::get_current_year(); i >= 1920; i--)
        combo_year->append(Glib::ustring::format(i));

    combo_day->set_active_text(Glib::ustring::format(util::Date::get_current_day()));
    combo_month->set_active_text(Glib::ustring(util::Date::get_current_month() < 10 ? "0" : "").append(
            Glib::ustring::format(util::Date::get_current_month())));
    combo_year->set_active_text(Glib::ustring::format(util::Date::get_current_year()));

    first_name->set_text("");
    last_name->set_text("");
    fiscal_code->set_text("");
    health_code->set_text("");
    street->set_text("");
    civic->set_text("");
    zip_code->set_text("");
    city->set_text("");
    country->set_text("");
    birth_city->set_text("");
    birth_country->set_text("");
}
