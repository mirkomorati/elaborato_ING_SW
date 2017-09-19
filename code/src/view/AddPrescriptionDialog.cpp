//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/view/AddPrescriptionDialog.hpp"

mm::view::AddPrescriptionDialog::AddPrescriptionDialog() : Dialog("addPrescriptionDialog") {

}

void mm::view::AddPrescriptionDialog::set_combo_box(std::vector<std::string> text) {
    auto &refBuilder = mm::RefBuilder::get_instance();
    Gtk::ComboBoxText *add_drug_ids[5];
    for (int i = 1; i <= 5; i++) {
        std::stringstream ss;
        ss << "addDrugId" << i;
        refBuilder.get_widget(ss.str(), add_drug_ids[i - 1]);

        for (auto &s : text) {
            add_drug_ids[i - 1]->append(s);
        }
    }
}

void mm::view::AddPrescriptionDialog::set_ok_handler(mm::controller::Dialog *controller,
                                                     void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("addPrescriptionOk", button);
    c_ok = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::AddPrescriptionDialog::set_cancel_handler(mm::controller::Dialog *controller,
                                                         void (controller::Dialog::*handler)(void)) {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("addPrescriptionCancel", button);
    c_cancel = button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}
