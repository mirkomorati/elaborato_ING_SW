//
// Created by Mirko Morati on 03/08/17.
//

#include "../../hdr/view/SelectDateByDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::view::SelectDateByDialog::show_dialog() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("selectDateByDialog", dialog);

    dialog->show();
}

void mm::view::SelectDateByDialog::dispose_dialog() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("selectDateByDialog", dialog);
    dialog->close();
}

void mm::view::SelectDateByDialog::set_controller(mm::controller::SelectDateByDialog *controller) {
    Gtk::Button *select_date_ok;
    Gtk::Button *select_date_cancel;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("selectDateByOk", select_date_ok);
    refBuilder.get_widget("selectDateByCancel", select_date_cancel);

    select_date_ok->signal_clicked().connect(sigc::mem_fun(controller,
                                                           &mm::controller::SelectDateByDialog::ok_handler));
    select_date_cancel->signal_clicked().connect(sigc::mem_fun(controller,
                                                               &mm::controller::SelectDateByDialog::cancel_handler));
}
