//
// Created by Noè Murr on 04/12/2017.
//

#include "AboutDialog.hpp"
#include "RefBuilder.hpp"

mm::AboutDialog::AboutDialog() : active(true) {

}

void mm::AboutDialog::show() {
    Gtk::AboutDialog *dialog;
    RefBuilder::get_instance().get_widget("aboutDialog", dialog);
    dialog->show();
}

void mm::AboutDialog::dispose() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("aboutDialog", dialog);
    dialog->close();
    active = false;
    notify();
}

bool mm::AboutDialog::isActive() {
    return active;
}

void mm::AboutDialog::reset() {

}

void mm::AboutDialog::onLinkClicked() {
    Gtk::Window *mainWindow;
    //Gtk
    GError *error;
    RefBuilder::get_instance().get_widget("mainWindow", mainWindow);
    //gtk_show_uri_on_window(mainWindow,,GDK_CURRENT_TIME_STAMP, &error);
}
