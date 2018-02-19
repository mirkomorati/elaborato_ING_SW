//
// Created by Noè Murr on 04/12/2017.
//

#include "AboutDialog.hpp"
#include "RefBuilder.hpp"

mm::AboutDialog::AboutDialog() : active(true) {
    Gtk::AboutDialog *dialog;
    RefBuilder::get_instance().get_widget("aboutDialog", dialog);

    dialog->signal_response().connect(sigc::mem_fun(this, &mm::AboutDialog::onResponse));
    dialog->signal_delete_event().connect(sigc::mem_fun(this, &mm::AboutDialog::onDelete));
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

void mm::AboutDialog::onResponse(int id) {
    switch (id) {
        case Gtk::ResponseType::RESPONSE_CLOSE:
        case Gtk::ResponseType::RESPONSE_CANCEL:
        case Gtk::ResponseType::RESPONSE_DELETE_EVENT:
            dispose();
            break;

        default:
            throw std::logic_error("unexpected response");
    }
}
