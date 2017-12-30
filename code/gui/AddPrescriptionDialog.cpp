//
// Created by Mirko Morati on 30/11/17.
//

#include <gtkmm/button.h>
#include "AddPrescriptionDialog.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Patient.hpp"

mm::AddPrescriptionDialog::AddPrescriptionDialog() : is_active(true),
                                                     issueDate("addIssueDateDay", "addIssueDateMonth",
                                                               "addIssueDateYear"),
                                                     expireDate("addExpireDateDay", "addExpireDateMonth",
                                                                "addExpireDateYear") {
    auto refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);

    refBuilder.get_widget("addDrugIdComboBox", drugComboBox);
    refBuilder.get_widget("addDrugIdsListBox", drugListBox);
    refBuilder.get_widget("addDrugIdAdd", drugAdd);

    reset();
    drugAdd->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::drugAddHandler));
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

    if (drugComboBox->get_active_text().empty()) init();

    patientID->set_text(static_cast<Glib::ustring>((*patientSel)[model::Patient::patientTreeModel.fiscal_code]));
    prescriptionID->set_text(Glib::ustring(to_string(model::Prescription::generateID())));

    issueDate.reset();
    expireDate.reset();
}

void mm::AddPrescriptionDialog::init() {
    model::Drug tmpDrug;
    vector<map<string, Serialized>> drugs;

    try {
        drugs = DBMaster::get_instance().get_rows(tmpDrug.get_table_name());
    }
    catch (const record_not_found_error &) {
        throw std::logic_error("cannot find drug table");
    }

    for (auto &drug : drugs) {
        const Glib::ustring &item = Glib::ustring().format(
                drug["name"].get_str(), " - ", drug["pharmaceutical_form"].get_str());
        drugComboBox->append(item);
    }
}

void mm::AddPrescriptionDialog::drugAddHandler() {
    Gtk::Label *addDrugError;
    Gtk::Label *addDrugOverError;
    RefBuilder::get_instance().get_widget("addDrugAddError", addDrugError);
    RefBuilder::get_instance().get_widget("addDrugOverError", addDrugOverError);

    if (drugComboBox->get_active_text().empty()) {
        addDrugError->set_visible(true);
        return;
    } else if (addDrugError->get_visible()) {
        addDrugError->set_visible(false);
    }
    if (drugEntries.size() == 5) {
        addDrugOverError->set_visible(true);
        return;
    } else if (addDrugOverError->get_visible()) {
        addDrugOverError->set_visible(false);
    }

    std::unique_ptr<mm::view::DrugEntry> tmp(new mm::view::DrugEntry(drugComboBox->get_active_text()));
    drugListBox->append(*tmp);
    tmp->signal_removed().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::drugRemoveHandler));
    drugEntries.push_back(std::move(tmp));
    drugListBox->show_all();
}

void mm::AddPrescriptionDialog::drugRemoveHandler(mm::view::DrugEntry *removed) {
    Gtk::Label *addDrugOverError;
    RefBuilder::get_instance().get_widget("addDrugOverError", addDrugOverError);
    if (addDrugOverError->is_visible()) addDrugOverError->set_visible(false);

    drugListBox->remove(*removed);
    drugEntries.erase(
            std::remove_if(drugEntries.begin(), drugEntries.end(),
                           [&](std::unique_ptr<mm::view::DrugEntry> const &p) {
                        return removed == p.get();
                    }),
            drugEntries.end());
}
