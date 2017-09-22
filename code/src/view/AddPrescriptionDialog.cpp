//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/view/AddPrescriptionDialog.hpp"
#include "../../hdr/time_utilities/Date.hpp"

mm::view::AddPrescriptionDialog::AddPrescriptionDialog() : Dialog("addPrescriptionDialog") {
    auto &refBuilder = mm::RefBuilder::get_instance();
    refBuilder.get_widget("addIssueDate", add_issue_date);
    refBuilder.get_widget("addExpireDate", add_expire_date);
    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);
    refBuilder.get_widget("addPatientId", add_patient_id);
    refBuilder.get_widget("addPrescriptionId", add_prescription_id);
    refBuilder.get_widget("addNegativeInteractions", add_negative_interactions);
    for (int i = 1; i <= 5; i++) {
        std::stringstream ss;
        ss << "addDrugId" << i;
        refBuilder.get_widget(ss.str(), add_drug_ids[i - 1]);
    }
    this->reset_view();
}

void mm::view::AddPrescriptionDialog::reset_view() {
    auto current_date = util::Date::get_current_date();
    add_issue_date->set_text(Glib::ustring(current_date.get_text()));
    add_expire_date->set_text(Glib::ustring((current_date + 30).get_text()));
    add_patient_id->set_text("");
    add_prescription_id->set_text("");
    add_negative_interactions->get_buffer()->set_text("");
}

void mm::view::AddPrescriptionDialog::set_combo_box(std::vector<std::string> text) {
    for (auto &add_drug_id : add_drug_ids) {
        for (auto &s : text) {
            add_drug_id->append(s);
        }
    }
}

void mm::view::AddPrescriptionDialog::set_ok_handler(mm::controller::Dialog *controller,
                                                     void (controller::Dialog::*handler)(void)) {
    c_ok = ok_button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}

void mm::view::AddPrescriptionDialog::set_cancel_handler(mm::controller::Dialog *controller,
                                                         void (controller::Dialog::*handler)(void)) {
    c_cancel = cancel_button->signal_clicked().connect(sigc::mem_fun(controller, handler));
}
