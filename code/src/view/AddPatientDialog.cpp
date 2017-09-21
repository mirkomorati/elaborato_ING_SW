//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/view/AddPatientDialog.hpp"

mm::view::AddPatientDialog::AddPatientDialog() : view::Dialog("addPatientDialog") {

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
    combo_day->set_active_text(Glib::ustring::format(date.month));
    combo_day->set_active_text(Glib::ustring::format(date.year));
}
