//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/view/SelectDateDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::view::SelectDateDialog::SelectDateDialog() : Dialog("selectDateDialog") {

}

void mm::view::SelectDateDialog::set_ok_handler(mm::controller::Dialog *controller,
                                                void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("selectDateOk", button);
    button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::SelectDateDialog::set_cancel_handler(mm::controller::Dialog *controller,
                                                    void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("selectDateCancel", button);
    button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}
