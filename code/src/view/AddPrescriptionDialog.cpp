//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/view/AddPrescriptionDialog.hpp"
#include "../../hdr/time_utilities/Date.hpp"

mm::view::AddPrescriptionDialog::AddPrescriptionDialog() : Dialog("addPrescriptionDialog") {
    auto &refBuilder = mm::RefBuilder::get_instance();
    Gtk::Entry *add_issue_date;
    Gtk::Entry *add_expire_date;
    refBuilder.get_widget("addIssueDate", add_issue_date);
    refBuilder.get_widget("addExpireDate", add_expire_date);

    auto current_date = util::Date::get_current_date();
    add_issue_date->set_text(Glib::ustring(current_date.get_text()));
    add_expire_date->set_text(Glib::ustring((current_date + 30).get_text()));
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
