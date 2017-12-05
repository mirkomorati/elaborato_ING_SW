//
// Created by Mirko Morati on 30/11/17.
//

#include <gtkmm/button.h>
#include "AddPrescriptionDialog.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Drug.hpp"

mm::AddPrescriptionDialog::AddPrescriptionDialog() : is_active(true), addPatientId("addPatientId"),
                                                     addPrescriptionId("addPrescriptionId"),
                                                     issueDate("addIssueDateDay", "addIssueDateMonth",
                                                               "addIssueDateYear"),
                                                     expireDate("addExpireDateDay", "addExpireDateMonth",
                                                                "addExpireDateYear") {
    auto refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);

    refBuilder.get_widget("addDrugId1", addDrugId1);
    refBuilder.get_widget("addDrugId2", addDrugId2);
    refBuilder.get_widget("addDrugId3", addDrugId3);
    refBuilder.get_widget("addDrugId4", addDrugId4);
    refBuilder.get_widget("addDrugId5", addDrugId5);

    reset();

    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::cancelHandler));
}

void mm::AddPrescriptionDialog::show() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addPrescriptionDialog", dialog);
    dialog->show();
}

void mm::AddPrescriptionDialog::dispose() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPrescriptionDialog", dialog);
    dialog->close();
    is_active = false;
    notify();
}

bool mm::AddPrescriptionDialog::isActive() {
    return is_active;
}

void mm::AddPrescriptionDialog::okHandler() {
    // todo gestire ok, validazione prescrizioni
    dispose();
}

void mm::AddPrescriptionDialog::cancelHandler() {
    dispose();
}

void mm::AddPrescriptionDialog::reset() {
    addPatientId.reset();
    addPrescriptionId.reset();
    issueDate.reset();
    expireDate.reset();

    model::Drug tmp;
    vector<map<string, Serialized>> drugs;

    try {
        drugs = DBMaster::get_instance().get_rows(tmp.get_table_name());
    }
    catch (const record_not_found_error &) {

    }

    for (auto &drug : drugs) {
        const Glib::ustring &item = Glib::ustring().format(
                drug["name"].get_str(), " - ", drug["pharmaceutical_form"].get_str());
        addDrugId1->append(item);
        addDrugId2->append(item);
        addDrugId3->append(item);
        addDrugId4->append(item);
        addDrugId5->append(item);
    }
}