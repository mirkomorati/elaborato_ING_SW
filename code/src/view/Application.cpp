//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/Application.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/controller/Register.hpp"

/*

void mm::view::Application::set_prescription_tree_model(
        model::Prescription::TreeModel &prescription_tree_model,
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
    for (int i = 0; i < 7; i++) {
        prescription_tree_view->get_column_cell_renderer(i)->property_xalign().set_value(0);
        prescription_tree_view->get_column(i)->set_min_width(100);
        prescription_tree_view->get_column(i)->set_resizable(true);
        prescription_tree_view->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        prescription_tree_view->get_column_cell_renderer(i)->set_property("ellipsize",
                                                                          Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    prescription_tree_view->set_model(prescription_list_store);
}

void mm::view::Application::set_drug_tree_model(mm::model::Drug::TreeModel &drug_tree_model,
                                                Glib::RefPtr<Gtk::ListStore> drug_list_store) {
    RefBuilder::get_instance().get_widget("drugTreeView", drug_tree_view);
    // Non il metodo migliore
    drug_tree_view->remove_all_columns();

    drug_tree_view->append_column("Nome",
                                  drug_tree_model.name);
    drug_tree_view->append_column("Forma Farmaceutica",
                                  drug_tree_model.pharmaceutical_form);
    drug_tree_view->append_column("Classificazione ATC",
                                  drug_tree_model.ATC_classification);
    drug_tree_view->append_column("Controindicazioni",
                                  drug_tree_model.contraindications);
    drug_tree_view->append_column("Principi Attivi",
                                  drug_tree_model.active_principles);
    drug_tree_view->append_column("Prezzo",
                                  drug_tree_model.price);
    for (int i = 0; i < 6; i++) {
        drug_tree_view->get_column(i)->set_min_width(100);
        drug_tree_view->get_column(i)->set_resizable(true);
        drug_tree_view->get_column_cell_renderer(i)->property_xalign().set_value(0);
        drug_tree_view->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        drug_tree_view->get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    drug_tree_view->set_model(drug_list_store);
}

void mm::view::Application::unselect_patient() const {
    patient_tree_view->get_selection()->unselect_all();
    unset_prescription_model();
}

void mm::view::Application::unselect_prescription() const {
    prescription_tree_view->get_selection()->unselect_all();
    unset_drug_model();
}

void mm::view::Application::unselect_drug() const {
    drug_tree_view->get_selection()->unselect_all();
}

void mm::view::Application::unset_patient_model() const {
    patient_tree_view->unset_model();
    patient_tree_view->remove_all_columns();
}

void mm::view::Application::unset_prescription_model() const {
    prescription_tree_view->unset_model();
    prescription_tree_view->remove_all_columns();
}

void mm::view::Application::unset_drug_model() const {
    drug_tree_view->unset_model();
    drug_tree_view->remove_all_columns();
}*/

void mm::view::Application::update() {
    lock_guard<mutex> lg(model->mutex);

    if (model->selected_patient_row.second) {
        show_patient_details();
        model->selected_patient_row.second = false;
    }

    if (model->patient_tree_row_selected.second and not model->patient_tree_row_selected.first) {
        unselect_patient();
        model->patient_tree_row_selected.second = false;
    }

    if (model->prescription_tree_view_row_selected.second and not model->prescription_tree_view_row_selected.first) {
        unselect_prescription();
        model->prescription_tree_view_row_selected.second = false;
    }

    if (model->drug_tree_view_row_selected.second and not model->drug_tree_view_row_selected.first) {
        unselect_drug();
        model->drug_tree_view_row_selected.second = false;
    }

    if (model->patient_list_store.second or model->patient_tree_model.second) {
        set_patient_tree();
        model->patient_list_store.second = false;
        model->patient_tree_model.second = false;
    }

    if (model->prescription_list_store.second or model->prescription_tree_model.second) {
        set_prescription_tree();
        model->prescription_list_store.second = false;
        model->prescription_tree_model.second = false;
    }

    if (model->drug_list_store.second or model->drug_tree_model.second) {
        set_drug_tree();
        model->drug_list_store.second = false;
        model->drug_tree_model.second = false;
    }
}


mm::view::Application::Application(mm::controller::Application &c)
        : model(c.get_model()) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Button *select_date;
    Gtk::ToolButton *add_prescription;
    Gtk::ToolButton *add_patient;
    Gtk::ToolButton *remove_patient;
    Gtk::ToolButton *edit_patient;
    Gtk::TreeView *patient_tree_view;

    refBuilder.get_widget("addPatient", add_patient);
    refBuilder.get_widget("removePatient", remove_patient);
    refBuilder.get_widget("editPatient", edit_patient);
    refBuilder.get_widget("selectDateButton", select_date);
    refBuilder.get_widget("addPrescription", add_prescription);
    refBuilder.get_widget("patientTreeView", patient_tree_view);


    add_patient->signal_clicked().connect(sigc::mem_fun(
            &c, &mm::controller::Application::add_patient_handler));
    remove_patient->signal_clicked().connect(sigc::mem_fun(
            &c, &mm::controller::Application::remove_patient_handler));
    edit_patient->signal_clicked().connect(sigc::mem_fun(
            &c, &mm::controller::Application::edit_patient_handler));
    select_date->signal_clicked().connect(sigc::mem_fun(
            &c, &mm::controller::Application::select_date_by_handler));
    add_prescription->signal_clicked().connect(sigc::mem_fun(
            &c, &mm::controller::Application::add_prescription_handler));
    patient_tree_view->signal_row_activated().connect(sigc::mem_fun(
            &c, &mm::controller::Application::row_selected_handler));

    c.attach(this);
}

void mm::view::Application::show_patient_details() {
    auto &refBuilder = RefBuilder::get_instance();
    auto row = model->selected_patient_row.first;
    Gtk::Label *detail_first_name;
    Gtk::Label *detail_last_name;
    Gtk::Label *detail_fiscal_code;
    Gtk::Label *detail_health_code;
    Gtk::Label *detail_birth_date;
    Gtk::Label *detail_birth_place;
    Gtk::Label *detail_address;

    refBuilder.get_widget("detailFirstName", detail_first_name);
    refBuilder.get_widget("detailLastName", detail_last_name);
    refBuilder.get_widget("detailFiscalCode", detail_fiscal_code);
    refBuilder.get_widget("detailHealthCode", detail_health_code);
    refBuilder.get_widget("detailBirthDate", detail_birth_date);
    refBuilder.get_widget("detailBirthPlace", detail_birth_place);
    refBuilder.get_widget("detailAddress", detail_address);

    detail_first_name->set_label(row[model->patient_tree_model.first.first_name]);
    detail_last_name->set_label(row[model->patient_tree_model.first.last_name]);
    detail_fiscal_code->set_label(row[model->patient_tree_model.first.fiscal_code]);
    detail_health_code->set_label(row[model->patient_tree_model.first.health_code]);
    detail_birth_date->set_label(row[model->patient_tree_model.first.birth_date]);
    detail_birth_place->set_label(row[model->patient_tree_model.first.birth_place]);
    detail_address->set_label(row[model->patient_tree_model.first.address]);
}

void mm::view::Application::set_patient_tree() {
    Gtk::TreeView *treeView;
    RefBuilder::get_instance().get_widget("patientTreeView", treeView);

    treeView->append_column("Nome", model->patient_tree_model.first.first_name);
    treeView->append_column("Cognome", model->patient_tree_model.first.last_name);
    treeView->append_column("Cod. Fiscale", model->patient_tree_model.first.fiscal_code);
    treeView->set_model(model->patient_list_store.first);

    for (int i = 0; i <= 2; i++) {
        treeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
    }
}

void mm::view::Application::set_drug_tree() {
    Gtk::TreeView *treeView;
    RefBuilder::get_instance().get_widget("drugTreeView", treeView);
    // Non il metodo migliore
    treeView->remove_all_columns();

    treeView->append_column("Nome", model->drug_tree_model.first.name);
    treeView->append_column("Forma Farmaceutica", model->drug_tree_model.first.pharmaceutical_form);
    treeView->append_column("Classificazione ATC", model->drug_tree_model.first.ATC_classification);
    treeView->append_column("Controindicazioni", model->drug_tree_model.first.contraindications);
    treeView->append_column("Principi Attivi", model->drug_tree_model.first.active_principles);
    treeView->append_column("Prezzo", model->drug_tree_model.first.price);

    for (int i = 0; i < 6; i++) {
        treeView->get_column(i)->set_min_width(100);
        treeView->get_column(i)->set_resizable(true);
        treeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
        treeView->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        treeView->get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    treeView->set_model(model->drug_list_store.first);
}

void mm::view::Application::set_prescription_tree() {
    Gtk::TreeView *treeView;
    RefBuilder::get_instance().get_widget("prescriptionTreeView", treeView);
    // Non il metodo migliore
    treeView->remove_all_columns();

    treeView->append_column("Paziente", model->prescription_tree_model.first.patient_id);
    treeView->append_column("ID", model->prescription_tree_model.first.prescription_id);
    treeView->append_column("Data Emissione", model->prescription_tree_model.first.issue_date);
    treeView->append_column("Data Scadenza", model->prescription_tree_model.first.expire_date);
    treeView->append_column("Farmaci", model->prescription_tree_model.first.drug_ids);
    treeView->append_column("Interazioni", model->prescription_tree_model.first.negative_interactions);
    treeView->append_column("Usata", model->prescription_tree_model.first.used);

    for (int i = 0; i < 7; i++) {
        treeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
        treeView->get_column(i)->set_min_width(100);
        treeView->get_column(i)->set_resizable(true);
        treeView->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        treeView->get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    treeView->set_model(model->prescription_list_store.first);
}

void mm::view::Application::unselect_patient() {
    Gtk::TreeView *patient_tree_view;
    RefBuilder::get_instance().get_widget("patientTreeView", patient_tree_view);
    patient_tree_view->unset_model();
    patient_tree_view->remove_all_columns();
}

void mm::view::Application::unselect_prescription() {
    Gtk::TreeView *prescription_tree_view;
    RefBuilder::get_instance().get_widget("prescriptionTreeView", prescription_tree_view);
    prescription_tree_view->unset_model();
    prescription_tree_view->remove_all_columns();
}

void mm::view::Application::unselect_drug() {
    Gtk::TreeView *drug_tree_view;
    RefBuilder::get_instance().get_widget("drugTreeView", drug_tree_view);
    drug_tree_view->unset_model();
    drug_tree_view->remove_all_columns();
}





