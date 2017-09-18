//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/controller/AddPrescriptionDialog.hpp"
#include "../../hdr/view/AddPrescriptionDialog.hpp"
#include "../../hdr/DBMaster.hpp"

void mm::controller::AddPrescriptionDialog::ok_handler() {
    view->dispose_dialog();
}

void mm::controller::AddPrescriptionDialog::cancel_handler() {
    view->dispose_dialog();
}

void mm::controller::AddPrescriptionDialog::set_view() {
    view = new mm::view::AddPrescriptionDialog();
    view->set_button_handler(this, "addPrescriptionOk", &controller::AddPrescriptionDialog::ok_handler);
    view->set_button_handler(this, "addPrescriptionCancel", &controller::AddPrescriptionDialog::cancel_handler);
    mm::model::Drug drug;
    // questo potrebbe essere il metodo corretto, ma get_rows non funziona con chiavi primarie composte
    // drug.unserialize(mm::DBMaster::get_instance().get_rows(drug.get_table_name(), drug.get_primary_key(), .......))

    auto d = mm::DBMaster::get_instance().get_table(drug.get_table_name());
    std::vector<std::string> combo_text;
    for (auto &row : d) {
        std::stringstream ss;
        ss << row[0].get_str() << ": " << row[1].get_str();
        combo_text.push_back(ss.str());
    }
    view->set_combo_box(combo_text);
    std::cout << "after combo" << std::endl;
}

mm::controller::AddPrescriptionDialog::~AddPrescriptionDialog() {}

mm::controller::AddPrescriptionDialog::AddPrescriptionDialog() {
    this->set_view();
}
