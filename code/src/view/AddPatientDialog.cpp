//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/view/AddPatientDialog.hpp"

mm::view::AddPatientDialog::AddPatientDialog() : view::Dialog("addPatientDialog") {
    Gtk::ComboBoxText *combo_day, *combo_month, *combo_year;
    RefBuilder::get_instance().get_widget("addBirthDateDay", combo_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", combo_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", combo_year);
    for (int i = 1; i <= 31; i++)
        combo_day->append(Glib::ustring::format(i));
    for (int i = 1; i <= 12; i++)
        combo_month->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    for (int i = util::Date::get_current_year(); i >= 1920; i--)
        combo_year->append(Glib::ustring::format(i));
    this->set_add_birth_date();
}

void mm::view::AddPatientDialog::set_ok_handler(controller::Dialog *controller,
                                                void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("addPatientOk", button);
    c_ok = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::AddPatientDialog::set_cancel_handler(controller::Dialog *controller,
                                                    void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("addPatientCancel", button);
    c_cancel = button->signal_clicked().connect(sigc::mem_fun(controller, handler));

}

void mm::view::AddPatientDialog::set_select_date_handler(mm::controller::AddPatientDialog *controller,
                                                         void (controller::AddPatientDialog::*handler)(void)) {
    Gtk::ComboBoxText *combo_day, *combo_month, *combo_year;
    RefBuilder::get_instance().get_widget("addBirthDateDay", combo_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", combo_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", combo_year);

    connections.push_back(combo_day->signal_changed().connect(sigc::mem_fun(controller, handler)));
    connections.push_back(combo_month->signal_changed().connect(sigc::mem_fun(controller, handler)));
    connections.push_back(combo_year->signal_changed().connect(sigc::mem_fun(controller, handler)));
}

mm::view::AddPatientDialog::~AddPatientDialog() {
    for (auto &connection : connections)
        if (not connection.empty()) connection.disconnect();
}

void mm::view::AddPatientDialog::set_add_birth_date(mm::util::Date date) {
    Gtk::ComboBoxText *combo_day, *combo_month, *combo_year;
    RefBuilder::get_instance().get_widget("addBirthDateDay", combo_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", combo_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", combo_year);
    combo_day->set_active_text(Glib::ustring::format(date.day));
    combo_month->set_active_text(Glib::ustring(date.month < 10 ? "0" : "").append(Glib::ustring::format(date.month)));
    combo_year->set_active_text(Glib::ustring::format(date.year));
}

void mm::view::AddPatientDialog::set_add_birth_date() {
    Gtk::ComboBoxText *combo_day, *combo_month, *combo_year;
    RefBuilder::get_instance().get_widget("addBirthDateDay", combo_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", combo_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", combo_year);
    combo_day->set_active_text(Glib::ustring::format(util::Date::get_current_day()));
    combo_month->set_active_text(Glib::ustring(util::Date::get_current_month() < 10 ? "0" : "").append(
            Glib::ustring::format(util::Date::get_current_month())));
    combo_year->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
}
