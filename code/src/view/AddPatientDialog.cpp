//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/view/AddPatientDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::view::AddPatientDialog::show_dialog() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPatientDialog", dialog);

    dialog->show();
}

void mm::view::AddPatientDialog::dispose_dialog() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog", dialog);
    dialog->close();
}

void mm::view::AddPatientDialog::set_controller(mm::controller::AddPatientDialog *controller) {
    Gtk::Button *ok_button;
    Gtk::Button *cancel_button;
    auto ref_builder = RefBuilder::get_instance();

    ref_builder.get_widget("addPatientOk", ok_button);
    ref_builder.get_widget("addPatientCancel", cancel_button);

    ok_button->signal_clicked().connect(sigc::mem_fun(controller,
                                                      &mm::controller::AddPatientDialog::ok_handler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(controller,
                                                          &mm::controller::AddPatientDialog::cancel_handler));
}

