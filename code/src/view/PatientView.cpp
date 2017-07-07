//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/PatientView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::PatientView::PatientView(mm::PatientController *controller) : controller(controller) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Button *select_date;

    refBuilder.get_widget("addPatient", add_patient);
    refBuilder.get_widget("removePatient", remove_patient);
    refBuilder.get_widget("editPatient", edit_patient);
    refBuilder.get_widget("selectDateButton", select_date);

    add_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::add_patient_handler));
    remove_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::remove_patient_handler));
    edit_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::edit_patient_handler));
    select_date->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::select_date_handler));

}

void mm::PatientView::set_patient_tree_model(PatientTreeModel &patient_tree_model,
                                             Glib::RefPtr<Gtk::ListStore> patient_list_store) {

    RefBuilder::get_instance().get_widget("patientTreeView", patient_tree_view);

    patient_tree_view->append_column("Nome", patient_tree_model.first_name);
    patient_tree_view->append_column("Cognome", patient_tree_model.last_name);
    patient_tree_view->append_column("Cod. Fiscale", patient_tree_model.fiscal_code);
    patient_tree_view->set_model(patient_list_store);

    for (int i = 0; i <= 2; i++) {
        patient_tree_view->get_column_cell_renderer(
            i)->property_xalign().set_value(0);
    }

    patient_tree_view->signal_row_activated().connect(sigc::mem_fun(
        controller, &mm::PatientController::row_selected_handler));
}

void mm::PatientView::add_patient_show_dialog() {
    Gtk::Dialog *add_patient_dialog;
    Gtk::Button *ok_button;
    Gtk::Button *cancel_button;
    auto ref_builder = RefBuilder::get_instance();
    ref_builder.get_widget("addPatientDialog",
                                          add_patient_dialog);
    ref_builder.get_widget("addPatientOk", ok_button);
    ref_builder.get_widget("addPatientCancel", cancel_button);

    add_patient_dialog->show();

    ok_button->signal_clicked().connect(sigc::mem_fun(controller,
                                                      &PatientController::on_add_patient_dialog_ok_button_pressed));
    cancel_button->signal_clicked().connect(sigc::mem_fun(controller,
                                                          &PatientController::on_add_patient_dialog_cancel_button_pressed));
}

void mm::PatientView::patient_detail_show(Gtk::TreeModel::Row row,
                                          PatientTreeModel &patient_tree_model) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Entry *detail_first_name;
    Gtk::Entry *detail_last_name;
    Gtk::Entry *detail_fiscal_code;
    Gtk::Entry *detail_health_code;
    Gtk::Entry *detail_birth_date;
    Gtk::Entry *detail_birth_place;
    Gtk::Entry *detail_address;

    refBuilder.get_widget("detailFirstName", detail_first_name);
    refBuilder.get_widget("detailLastName", detail_last_name);
    refBuilder.get_widget("detailFiscalCode", detail_fiscal_code);
    refBuilder.get_widget("detailHealthCode", detail_health_code);
    refBuilder.get_widget("detailBirthDate", detail_birth_date);
    refBuilder.get_widget("detailBirthPlace", detail_birth_place);
    refBuilder.get_widget("detailAddress", detail_address);

    detail_first_name->set_text(row[patient_tree_model.first_name]);
    detail_last_name->set_text(row[patient_tree_model.last_name]);
    detail_fiscal_code->set_text(row[patient_tree_model.fiscal_code]);
    detail_health_code->set_text(row[patient_tree_model.health_code]);
    detail_birth_date->set_text(row[patient_tree_model.birth_date]);
    detail_birth_place->set_text(row[patient_tree_model.birth_place]);
    detail_address->set_text(row[patient_tree_model.address]);
}

void mm::PatientView::set_prescription_tree_model(
    PrescriptionTreeModel &prescription_tree_model,
    Glib::RefPtr<Gtk::ListStore> prescription_list_store) {
    RefBuilder::get_instance().get_widget("prescriptionTreeView",
                                          prescription_tree_view);
    // Non il metodo migliore
    prescription_tree_view->remove_all_columns();

    prescription_tree_view->append_column("Paziente",
                                          prescription_tree_model.patient_id);
    prescription_tree_view->append_column("ID",
                                          prescription_tree_model.prescription_id);
    prescription_tree_view->append_column("Data Emissione",
                                          prescription_tree_model.issue_date);
    prescription_tree_view->append_column("Data Scadenza",
                                          prescription_tree_model.expire_date);
    prescription_tree_view->append_column("Farmaci",
                                          prescription_tree_model.drug_ids);
    prescription_tree_view->append_column("Interazioni",
                                          prescription_tree_model.negative_interactions);
    prescription_tree_view->append_column("Usata",
                                          prescription_tree_model.used);
    for (int i = 0; i <= 6; i++) {
        prescription_tree_view->get_column_cell_renderer(
            i)->property_xalign().set_value(0);
    }

    prescription_tree_view->set_model(prescription_list_store);
}

void mm::PatientView::dispose_add_patient_dialog() {
    Gtk::Dialog *add_patient_dialog;
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPatientDialog",
                          add_patient_dialog);
    Gtk::Entry *first_name;
    Gtk::Entry *last_name;
    Gtk::Entry *fiscal_code;
    Gtk::Entry *health_code;
    Gtk::Entry *birth_date;
    Gtk::Entry *street;
    Gtk::Entry *civic;
    Gtk::Entry *zip_code;
    Gtk::Entry *city;
    Gtk::Entry *country;
    Gtk::Entry *birth_city;
    Gtk::Entry *birth_country;

    refBuilder.get_widget("addFirstName", first_name);
    refBuilder.get_widget("addLastName", last_name);
    refBuilder.get_widget("addFiscalCode", fiscal_code);
    refBuilder.get_widget("addHealthCode", health_code);
    refBuilder.get_widget("addBirthDate", birth_date);
    refBuilder.get_widget("addCity", birth_city);
    refBuilder.get_widget("addCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);

    first_name->set_text("");
    last_name->set_text("");
    fiscal_code->set_text("");
    health_code->set_text("");
    birth_date->set_text("");
    street->set_text("");
    civic->set_text("");
    zip_code->set_text("");
    city->set_text("");
    country->set_text("");
    birth_city->set_text("");
    birth_country->set_text("");

    add_patient_dialog->close();
}

void mm::PatientView::add_select_date_dialog() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("selectDateDialog", dialog);

    dialog->show();

}
