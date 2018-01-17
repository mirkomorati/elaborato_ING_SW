//
// Created by Mirko Morati on 30/11/17.
//

#include <gtkmm/button.h>
#include "AddPrescriptionDialog.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../model/Patient.hpp"
#include "../utils/Date.hpp"
#include "../utils/stringUtils.hpp"

#define UPDATE_PRESCRIPTIONS 2

mm::AddPrescriptionDialog::AddPrescriptionDialog() : is_active(true) {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::Dialog *dialog;

    refBuilder.get_widget("addPrescriptionOk", ok_button);
    refBuilder.get_widget("addPrescriptionCancel", cancel_button);

    refBuilder.get_widget("addDrugIdComboBox", drugComboBox);
    refBuilder.get_widget("addDrugIdsListBox", drugListBox);
    refBuilder.get_widget("addInteractionDrug1", interactionComboBox1);
    refBuilder.get_widget("addInteractionDrug2", interactionComboBox2);
    refBuilder.get_widget("addInteractionListBox", interactionListBox);
    refBuilder.get_widget("addDrugIdAdd", drugAdd);
    refBuilder.get_widget("addInteractionButton", interactionAdd);
    refBuilder.get_widget("addPrescriptionValidityMonth", monthComboBox);
    refBuilder.get_widget("addPrescriptionDialog", dialog);

    reset();

    monthComboBox->signal_changed().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::monthValidityChanged));
    drugAdd->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::drugAddHandler));
    interactionAdd->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::interactionAddHandler));
    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::cancelHandler));
    dialog->signal_delete_event().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::onDelete));
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
    dialog->hide();
    is_active = false;
    notify(UPDATE_PRESCRIPTIONS);
}

bool mm::AddPrescriptionDialog::isActive() {
    return is_active;
}

void mm::AddPrescriptionDialog::okHandler() {
    // todo gestire ok, validazione prescrizioni
    Gtk::Entry *prescriptionID;
    Gtk::Entry *patientID;
    Gtk::Entry *negativeInteractions;
    Gtk::Label *issueDate;
    Gtk::Label *expireDate;

    RefBuilder &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addPrescriptionId", prescriptionID);
    refBuilder.get_widget("addPatientId", patientID);
    refBuilder.get_widget("addIssueDate", issueDate);
    refBuilder.get_widget("addPrescriptionExpireDate", expireDate);
    model::Prescription tmp;

    tmp.set_patient_id(patientID->get_text());
    tmp.set_prescription_id(std::stoi(prescriptionID->get_text()));
    tmp.set_issue_date(issueDate->get_text());
    tmp.set_expire_date(expireDate->get_text());

    for (const auto &entry : drugEntries) {
        tmp.add_drug(entry->get_drugName(), entry->get_drugForm());
        std::cout << entry->get_drugForm() << std::endl;
    }

    map<string, string> interactions;
    for (const auto &entry : interactionEntries) {
        interactions[entry->get_drug1()] = entry->get_drug2();
    }

    tmp.set_negative_interactions(interactions);

    tmp.set_used(false);

    // todo da finire.

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
    Gtk::Label *monthLabel;
    Gtk::Label *issueDate;

    refBuilder.get_widget("mainWindow", mainWindow);
    refBuilder.get_widget("patientTreeView", patientTreeView);
    refBuilder.get_widget("addPatientId", patientID);
    refBuilder.get_widget("addPrescriptionId", prescriptionID);
    refBuilder.get_widget("addPrescriptionMonthLabel", monthLabel);
    refBuilder.get_widget("addIssueDate", issueDate);

    issueDate->set_text(mm::util::Date::get_current_date().get_as_text());

    Gtk::TreeModel::iterator patientSel;

    if (not patientTreeView->get_selection() or not(patientSel = patientTreeView->get_selection()->get_selected())) {
        Gtk::MessageDialog info(*mainWindow, "Nessun paziente selezionato", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        info.run();
        is_active = false;
        return;
    }

    if (drugComboBox->get_active_text().empty()) initDrugComboBox();
    if (monthComboBox->get_active_text().empty()) initMonthComboBox();

    monthComboBox->set_active_text("1");
    monthLabel->set_text("Mese");

    patientID->set_text(static_cast<Glib::ustring>((*patientSel)[model::Patient::patientTreeModel.fiscal_code]));
    prescriptionID->set_text(Glib::ustring(to_string(model::Prescription::generateID())));
}

void mm::AddPrescriptionDialog::initDrugComboBox() {
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

    const Glib::ustring &activeDrug = drugComboBox->get_active_text();
    if (activeDrug.empty()) {
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

    /*
    std::unique_ptr<mm::view::DrugEntry> tmp(new mm::view::DrugEntry(drugComboBox->get_active_text()));
    */
    std::unique_ptr<mm::view::DrugEntry> tmp(new mm::view::DrugEntry(activeDrug));
    drugListBox->append(*tmp);
    tmp->signal_removed().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::drugRemoveHandler));

    bool present = false;
    for (const auto &entry : drugEntries) {
        if (entry->get_drugName() == tmp->get_drugName()) {
            present = true;
            break;
        }
    }

    if (!present) {
        interactionComboBox1->append(tmp->get_drugName());
        interactionComboBox2->append(tmp->get_drugName());
    }

    drugEntries.push_back(std::move(tmp));
    drugListBox->show_all();
}

void mm::AddPrescriptionDialog::drugRemoveHandler(mm::view::DrugEntry *removed) {
    Gtk::Label *addDrugOverError;
    RefBuilder::get_instance().get_widget("addDrugOverError", addDrugOverError);
    if (addDrugOverError->is_visible()) addDrugOverError->set_visible(false);

    drugListBox->remove(*removed);
    drugEntries.erase(std::remove_if(drugEntries.begin(), drugEntries.end(),
                                     [&](std::unique_ptr<mm::view::DrugEntry> const &p) {
                                         return removed == p.get();
                                     }),
                      drugEntries.end());

    interactionComboBox1->remove_all();
    interactionComboBox2->remove_all();

    for (int i = 0; i < drugEntries.size(); ++i) {
        bool present = false;
        for (int j = 0; j < drugEntries.size(); ++j) {
            if (i != j and drugEntries[i]->get_drugName() == drugEntries[j]->get_drugName()) {
                present = true;
                break;
            }
        }

        if (!present) {
            interactionComboBox1->append(drugEntries[i]->get_drugName());
            interactionComboBox2->append(drugEntries[i]->get_drugName());
        }
    }
}

mm::AddPrescriptionDialog::~AddPrescriptionDialog() {
    for (auto &de : drugEntries) {
        drugListBox->remove(*de);
    }
}

void mm::AddPrescriptionDialog::initMonthComboBox() {
    for (int i = 1; i <= 12; i++) monthComboBox->append(Glib::ustring::format(i));
    monthComboBox->set_active_text("1");
    monthValidityChanged();
}

void mm::AddPrescriptionDialog::monthValidityChanged() {
    Gtk::Label *monthLabel;
    Gtk::Label *issueDate;
    Gtk::Label *expireDate;
    RefBuilder::get_instance().get_widget("addPrescriptionMonthLabel", monthLabel);
    RefBuilder::get_instance().get_widget("addPrescriptionExpireDate", expireDate);
    RefBuilder::get_instance().get_widget("addIssueDate", issueDate);

    if (monthComboBox->get_active_text() != "1") {
        monthLabel->set_text("Mesi");
    } else {
        monthLabel->set_text("Mese");
    }

    mm::util::Date date;
    date.set_from_str(issueDate->get_text());
    date.add_months((unsigned int) std::stoi(monthComboBox->get_active_text()));
    expireDate->set_text(date.get_as_text());
}

void mm::AddPrescriptionDialog::interactionAddHandler() {
    Gtk::Label *addInteractionError;
    RefBuilder::get_instance().get_widget("addInteractionError", addInteractionError);

    const Glib::ustring &drug1 = interactionComboBox1->get_active_text();
    const Glib::ustring &drug2 = interactionComboBox2->get_active_text();

    bool present = false;

    for (const auto &entry : interactionEntries) {
        if ((entry->get_drug1() == drug1.c_str() and entry->get_drug2() == drug2.c_str())
            or (entry->get_drug1() == drug2.c_str() and entry->get_drug2() == drug1.c_str())) {
            present = true;
            break;
        }
    }
    if (drug1.empty() or drug2.empty() or drug1 == drug2 or present or interactionEntries.size() >= 5) {
        addInteractionError->set_visible(true);
        return;
    } else if (addInteractionError->get_visible()) {
        addInteractionError->set_visible(false);
    }

    std::unique_ptr<mm::view::InteractionEntry> tmp(new mm::view::InteractionEntry(drug1, drug2));
    interactionListBox->append(*tmp);
    tmp->signal_removed().connect(sigc::mem_fun(this, &mm::AddPrescriptionDialog::interactionRemoveHandler));
    interactionEntries.push_back(std::move(tmp));
    interactionListBox->show_all();
}

void mm::AddPrescriptionDialog::interactionRemoveHandler(mm::view::InteractionEntry *removed) {
    Gtk::Label *addInteractionError;
    RefBuilder::get_instance().get_widget("addInteractionError", addInteractionError);
    if (addInteractionError->is_visible()) addInteractionError->set_visible(false);

    interactionListBox->remove(*removed);
    interactionEntries.erase(std::remove_if(interactionEntries.begin(), interactionEntries.end(),
                                            [&](std::unique_ptr<mm::view::InteractionEntry> const &p) {
                                                return removed == p.get();
                                            }),
                             interactionEntries.end());
}