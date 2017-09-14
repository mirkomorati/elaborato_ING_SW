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
    patient.set_birth_date(birth_date->get_text());

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

void mm::controller::AddPatientDialog::show_dialog() {
    view->show_dialog();
}

void mm::controller::AddPatientDialog::set_view() {
    view = new mm::view::AddPatientDialog();
    view->set_controller(this);
}

mm::controller::AddPatientDialog::~AddPatientDialog() {
    delete (view);
}

void mm::controller::AddPatientDialog::set_parent(mm::controller::Patient *parent) {
    AddPatientDialog::parent = parent;
}
