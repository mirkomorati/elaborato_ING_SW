//
// Created by Mirko Morati on 14/09/17.
//

#include <gtkmm/dialog.h>
#include "../../hdr/view/Dialog.hpp"

mm::view::Dialog::Dialog(std::string name) : name(name) {
}

void mm::view::Dialog::show_dialog() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget(name, dialog);

    dialog->show();
}

void mm::view::Dialog::dispose_dialog() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget(name, dialog);
    dialog->close();
}
