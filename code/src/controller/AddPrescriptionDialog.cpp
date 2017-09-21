//
// Created by Mirko Morati on 18/09/17.
//

#include "../../hdr/controller/AddPrescriptionDialog.hpp"
#include "../../hdr/DBMaster.hpp"

void mm::controller::AddPrescriptionDialog::ok_handler() {
    this->free();
}

void mm::controller::AddPrescriptionDialog::cancel_handler() {
    this->free();
}

void mm::controller::AddPrescriptionDialog::set_view() {
    view = new mm::view::AddPrescriptionDialog();
    view->set_ok_handler(this, &controller::Dialog::ok_handler);
    view->set_cancel_handler(this, &controller::Dialog::cancel_handler);
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
}

mm::controller::AddPrescriptionDialog::~AddPrescriptionDialog() {
    delete view;
}

mm::controller::AddPrescriptionDialog::AddPrescriptionDialog() {
    this->set_view();
}

void mm::controller::AddPrescriptionDialog::free() {
    view->dispose_dialog();
    delete this;
}

mm::controller::Dialog *mm::controller::AddPrescriptionDialog::create() {
    return new AddPrescriptionDialog();
}

void mm::controller::AddPrescriptionDialog::show_dialog() {
    view->show_dialog();
}
