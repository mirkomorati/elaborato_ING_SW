//
// Created by Mirko Morati on 14/09/17.
//

#include <iostream>
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/controller/AddPatientDialog.hpp"
#include "../../hdr/DBMaster.hpp"

void mm::controller::AddPatientDialog::ok_handler() {
    auto &refBuilder = RefBuilder::get_instance();
    model::Patient patient;
    stringstream address;
    stringstream birth_address;

    // fields
    Gtk::Entry *first_name;
    Gtk::Entry *last_name;
    Gtk::Entry *fiscal_code;
    Gtk::Entry *health_code;
    Gtk::Button *birth_date;
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
    refBuilder.get_widget("addBirthCity", birth_city);
    refBuilder.get_widget("addBirthCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);

    patient.set_first_name(first_name->get_text());
    patient.set_last_name(last_name->get_text());
    patient.set_fiscal_code(fiscal_code->get_text());
    patient.set_health_code(health_code->get_text());
    patient.set_birth_date(birth_date->get_label());

    address << street->get_text() << " " << civic->get_text() << ", " << zip_code->get_text() << ", "
            << city->get_text() << ", " << country->get_text();

    birth_address << birth_city->get_text() << ", " << birth_country->get_text();

    patient.set_address(address.str());
    patient.set_doctor_id(parent->get_doctor().get_regional_id());

    DBMaster::get_instance().add_to_db(patient);

    view->dispose_dialog();
    // todo: devo riaggiornare la view dei pazienti con quello appena aggiunto, sembra che questo metodo non funzioni
    // parent->set_doctor(parent->get_doctor().get_regional_id());
}

void mm::controller::AddPatientDialog::cancel_handler() {
    view->dispose_dialog();
}

void mm::controller::AddPatientDialog::set_view() {
    view = new mm::view::AddPatientDialog();
    view->set_button_handler(this, "addPatientOk", &controller::AddPatientDialog::ok_handler);
    view->set_button_handler(this, "addPatientCancel", &controller::AddPatientDialog::cancel_handler);
    view->set_button_handler(this, "addBirthDate", &controller::AddPatientDialog::select_birth_date_handler);

}

mm::controller::AddPatientDialog::~AddPatientDialog() {
    delete (view);
}

void mm::controller::AddPatientDialog::set_parent(mm::controller::Patient *parent) {
    AddPatientDialog::parent = parent;
}

void mm::controller::AddPatientDialog::select_birth_date_handler() {
    mm::controller::SelectDateDialog *select_date_controller = new mm::controller::SelectDateDialog();
    select_date_controller->set_view();
    select_date_controller->set_parent(this);
    select_date_controller->show_dialog();
}

void mm::controller::AddPatientDialog::select_birth_date_get_date(util::Date date) {
    Gtk::Button *add_birth_date;
    RefBuilder::get_instance().get_widget("addBirthDate", add_birth_date);
    add_birth_date->set_label(date.get_text());
}