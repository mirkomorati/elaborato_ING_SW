//
// Created by Mirko Morati on 03/08/17.
//

#include "../../hdr/view/SelectDateDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::view::SelectDateDialog::show_dialog() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("selectDateDialog", dialog);

    dialog->show();
}

void mm::view::SelectDateDialog::dispose_dialog() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("selectDateDialog", dialog);
    dialog->close();
}

void mm::view::SelectDateDialog::set_controller(mm::controller::SelectDateDialog *controller) {
    Gtk::Button *select_date_ok;
    Gtk::Button *select_date_cancel;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("selectDateOk", select_date_ok);
    refBuilder.get_widget("selectDateCancel", select_date_cancel);

    select_date_ok->signal_clicked().connect(sigc::mem_fun(controller,
                                                           &mm::controller::SelectDateDialog::ok_handler));
    select_date_cancel->signal_clicked().connect(sigc::mem_fun(controller,
                                                               &mm::controller::SelectDateDialog::cancel_handler));
}
