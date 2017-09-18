//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/controller/AddPrescriptionDialog.hpp"
#include "../../hdr/view/AddPrescriptionDialog.hpp"

void mm::controller::AddPrescriptionDialog::ok_handler() {
    view->dispose_dialog();
}

void mm::controller::AddPrescriptionDialog::cancel_handler() {
    view->dispose_dialog();
}

void mm::controller::AddPrescriptionDialog::set_view() {
    view = new mm::view::AddPrescriptionDialog();
    view->set_button_handler(this, "addPrescriptionOk", &controller::AddPrescriptionDialog::ok_handler);
    view->set_button_handler(this, "addPrescriptionCancel", &controller::AddPrescriptionDialog::cancel_handler);
}

void mm::controller::AddPrescriptionDialog::set_parent(mm::controller::Patient *parent) {

}

mm::controller::AddPrescriptionDialog::~AddPrescriptionDialog() {
    delete parent;
}
