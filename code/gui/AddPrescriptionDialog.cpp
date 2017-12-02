//
// Created by Mirko Morati on 30/11/17.
//

#include <gtkmm/button.h>
#include "AddPrescriptionDialog.hpp"
#include "../RefBuilder.hpp"

mm::AddPrescriptionDialog::AddPrescriptionDialog() {
    is_active = true;
    auto refBuilder = RefBuilder::get_instance();
    // todo sistemare tutti i pezzi.. fare wrapper per entry ed altro ..?
    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);

    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::cancelHandler));
}

void mm::AddPrescriptionDialog::show() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addPrescriptionDialog", dialog);
    dialog->show();
}

void mm::AddPrescriptionDialog::dispose() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPrescriptionDialog", dialog);
    dialog->close();
    is_active = false;
    notify();
}

bool mm::AddPrescriptionDialog::isActive() {
    return is_active;
}

void mm::AddPrescriptionDialog::okHandler() {
    // todo gestire ok
    dispose();
}

void mm::AddPrescriptionDialog::cancelHandler() {
    dispose();
}

void mm::AddPrescriptionDialog::reset() {

}
