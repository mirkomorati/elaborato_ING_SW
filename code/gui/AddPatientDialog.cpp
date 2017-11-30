//
// Created by Mirko Morati on 30/11/17.
//

#include "AddPatientDialog.hpp"
#include "../RefBuilder.hpp"

mm::AddPatientDialog::AddPatientDialog() {
    is_active = true;

    Gtk::Button *ok_button;
    Gtk::Button *cancel_button;
    RefBuilder::get_instance().get_widget("addPatientOk", ok_button);
    RefBuilder::get_instance().get_widget("addPatientCancel", cancel_button);

    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::cancelHandler));
}

void mm::AddPatientDialog::show() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addPatientDialog", dialog);
    dialog->show();
}

bool mm::AddPatientDialog::isActive() {
    return is_active;
}

void mm::AddPatientDialog::okHandler() {
    // todo gestire ok
    dispose();
}

void mm::AddPatientDialog::cancelHandler() {
    dispose();
}

void mm::AddPatientDialog::dispose() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog", dialog);
    dialog->close();
    is_active = false;
    notify();
}

