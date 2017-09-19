//
// Created by Mirko Morati on 03/08/17.
//

#include "../../hdr/view/SelectDateByDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::view::SelectDateByDialog::SelectDateByDialog() : view::Dialog("selectDateByDialog") {

}

void mm::view::SelectDateByDialog::set_ok_handler(mm::controller::Dialog *controller,
                                                  void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("selectDateByOk", button);
    c_ok = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::SelectDateByDialog::set_cancel_handler(mm::controller::Dialog *controller,
                                                      void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("selectDateByCancel", button);
    c_cancel = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}
