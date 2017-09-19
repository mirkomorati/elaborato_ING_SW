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
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("addBirthDate", button);
    c_select_date = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

mm::view::AddPatientDialog::~AddPatientDialog() {
    c_ok.disconnect();
    c_cancel.disconnect();
    c_select_date.disconnect();
}
