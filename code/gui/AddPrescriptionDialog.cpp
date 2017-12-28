//
// Created by Mirko Morati on 30/11/17.
//

#include <gtkmm/button.h>
#include "AddPrescriptionDialog.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Drug.hpp"
#include "../model/Patient.hpp"
#include "view/CustomWidgets.hpp"

mm::AddPrescriptionDialog::AddPrescriptionDialog() : is_active(true),
                                                     issueDate("addIssueDateDay", "addIssueDateMonth",
                                                               "addIssueDateYear"),
                                                     expireDate("addExpireDateDay", "addExpireDateMonth",
                                                                "addExpireDateYear") {
    auto refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);

    refBuilder.get_widget("addDrugId1", drugCombos[0]);
    refBuilder.get_widget("addDrugId2", drugCombos[1]);
    refBuilder.get_widget("addDrugId3", drugCombos[2]);
    refBuilder.get_widget("addDrugId4", drugCombos[3]);
    refBuilder.get_widget("addDrugId5", drugCombos[4]);

    reset();

    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::cancelHandler));
}

void mm::AddPrescriptionDialog::show() {
    if (not isActive()) {
        notify();
        return;
    }
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
    Gtk::Entry *prescriptionID;
    RefBuilder::get_instance().get_widget("addPrescriptionId", prescriptionID);
    model::Prescription tmp;

    if (DBMaster::get_instance().exists(tmp.get_table_name(), tmp.get_primary_key()[0],
                                        stoi(prescriptionID->get_text().c_str()))) {
        cout << "esiste\n";
    } else {
        cout << "non esiste\n";
    }

    dispose();
}

void mm::AddPrescriptionDialog::cancelHandler() {
    dispose();
}

void mm::AddPrescriptionDialog::reset() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::Entry *patientID;
    Gtk::Entry *prescriptionID;
    Gtk::Window *mainWindow;
    Gtk::TreeView *patientTreeView;
    model::Prescription tmpPrescription;
    model::Drug tmpDrug;
    vector<map<string, Serialized>> drugs;
    vector<map<string, Serialized>> prescriptions;

    refBuilder.get_widget("mainWindow", mainWindow);
    refBuilder.get_widget("patientTreeView", patientTreeView);
    refBuilder.get_widget("addPatientId", patientID);
    refBuilder.get_widget("addPrescriptionId", prescriptionID);
    Gtk::TreeModel::iterator patientSel;

    if (not patientTreeView->get_selection() or not(patientSel = patientTreeView->get_selection()->get_selected())) {
        Gtk::MessageDialog info(*mainWindow, "Nessun paziente selezionato", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        info.run();
        is_active = false;
        return;
    }

    patientID->set_text(static_cast<Glib::ustring>((*patientSel)[model::Patient::patientTreeModel.fiscal_code]));
    prescriptionID->set_text(Glib::ustring(to_string(model::Prescription::generateID())));

    try {
        drugs = DBMaster::get_instance().get_rows(tmpDrug.get_table_name());
    }
    catch (const record_not_found_error &) {
        throw std::logic_error("cannot find drug table");
    }

    for (auto &combo : drugCombos) combo->remove_all();

    for (auto &drug : drugs) {
        const Glib::ustring &item = Glib::ustring().format(
                drug["name"].get_str(), " - ", drug["pharmaceutical_form"].get_str());
        for (auto &combo : drugCombos)
            combo->append(item);
    }

    issueDate.reset();
    expireDate.reset();
}