//
// Created by Mirko Morati on 30/11/17.
//

#include <spdlog/spdlog.h>
#include "AddPatientDialog.hpp"
#include "../RefBuilder.hpp"
#include "../model/Patient.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"
#include "../utils/Date.hpp"

mm::AddPatientDialog::AddPatientDialog() {
    is_active = true;

    Gtk::Button *ok_button;
    Gtk::Button *cancel_button;
    Gtk::ComboBoxText *add_birth_day;
    Gtk::ComboBoxText *add_birth_month;
    Gtk::ComboBoxText *add_birth_year;

    RefBuilder::get_instance().get_widget("addPatientOk", ok_button);
    RefBuilder::get_instance().get_widget("addPatientCancel", cancel_button);
    RefBuilder::get_instance().get_widget("addBirthDateDay", add_birth_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", add_birth_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", add_birth_year);

    add_birth_day->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    add_birth_month->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    add_birth_year->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::cancelHandler));

    reset();
}

void mm::AddPatientDialog::show() {
    Gtk::Dialog *dialog;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("addPatientDialog", dialog);
    dialog->show();
}

bool mm::AddPatientDialog::isActive() {
    return is_active;
}

void mm::AddPatientDialog::birthDateChanged() {
    auto log = spdlog::get("out");

    Gtk::ComboBoxText *add_birth_day;
    Gtk::ComboBoxText *add_birth_month;
    Gtk::ComboBoxText *add_birth_year;
    util::Date date;
    int day, month, year;

    RefBuilder::get_instance().get_widget("addBirthDateDay", add_birth_day);
    RefBuilder::get_instance().get_widget("addBirthDateMonth", add_birth_month);
    RefBuilder::get_instance().get_widget("addBirthDateYear", add_birth_year);

    day = std::atoi(add_birth_day->get_active_text().c_str());
    month = std::atoi(add_birth_month->get_active_text().c_str());
    year = std::atoi(add_birth_year->get_active_text().c_str());
    date = util::Date(day, month, year);

    log->info("[AddPatientDialog] Validating date: {}", date.get_text());

    if (!date.is_valid()) {
        if ((date.day >= 29 && date.day <= 31) && date.month == 2) {
            add_birth_day->set_active_text(Glib::ustring("28"));
            add_birth_month->set_active_text(Glib::ustring("02"));
            add_birth_year->set_active_text(Glib::ustring::format(date.year));
        } else {
            add_birth_day->set_active_text(Glib::ustring("30"));
            add_birth_month->set_active_text(Glib::ustring::format(date.month));
            add_birth_year->set_active_text(Glib::ustring::format(date.year));
        }
    }
}

void mm::AddPatientDialog::okHandler() {
    auto log = spdlog::get("out");

    mm::model::Patient patient;
    stringstream address;
    stringstream birth_address;
    stringstream birth_date;
    auto refBuilder = RefBuilder::get_instance();

    Gtk::Entry *first_name;
    Gtk::Entry *last_name;
    Gtk::Entry *fiscal_code;
    Gtk::Entry *health_code;
    Gtk::Entry *street;
    Gtk::Entry *civic;
    Gtk::Entry *zip_code;
    Gtk::Entry *city;
    Gtk::Entry *country;
    Gtk::Entry *birth_city;
    Gtk::Entry *birth_country;
    Gtk::ComboBoxText *add_birth_day;
    Gtk::ComboBoxText *add_birth_month;
    Gtk::ComboBoxText *add_birth_year;

    refBuilder.get_widget("addFirstName", first_name);
    refBuilder.get_widget("addLastName", last_name);
    refBuilder.get_widget("addFiscalCode", fiscal_code);
    refBuilder.get_widget("addHealthCode", health_code);
    refBuilder.get_widget("addBirthCity", birth_city);
    refBuilder.get_widget("addBirthCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);
    refBuilder.get_widget("addBirthDateDay", add_birth_day);
    refBuilder.get_widget("addBirthDateMonth", add_birth_month);
    refBuilder.get_widget("addBirthDateYear", add_birth_year);

    patient.set_first_name(first_name->get_text());
    patient.set_last_name(last_name->get_text());
    patient.set_fiscal_code(fiscal_code->get_text());
    patient.set_health_code(health_code->get_text());
    birth_date << add_birth_day->get_active_text().c_str() << "/"
               << add_birth_month->get_active_text().c_str() << "/"
               << add_birth_year->get_active_text().c_str();
    patient.set_birth_date(birth_date.str());

    address << street->get_text() << " "
            << civic->get_text() << ", "
            << zip_code->get_text() << ", "
            << city->get_text() << ", "
            << country->get_text();

    birth_address << birth_city->get_text() << ", "
                  << birth_country->get_text();

    patient.set_address(address.str());
    patient.set_doctor_id(mm::model::authentication::Login::get_instance().regional_id);
    patient.set_birth_place(birth_address.str());

    log->info("[AddPatientDialog] Validating patient");
    if (patient.is_valid()) {
        DBMaster::get_instance().add_to_db(patient);
        dispose();
    } else {
        Gtk::Label *error;
        refBuilder.get_widget("addPatientError", error);
        error->set_visible(true);
    }
}

void mm::AddPatientDialog::cancelHandler() {
    auto log = spdlog::get("out");
    log->info("[AddPatientDialog] Cancel dialog");
    dispose();
}

void mm::AddPatientDialog::dispose() {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog", dialog);
    dialog->close();
    is_active = false;
    notify();
}

void mm::AddPatientDialog::reset() {
    auto log = spdlog::get("out");
    auto refBuilder = RefBuilder::get_instance();

    Gtk::Entry *first_name;
    Gtk::Entry *last_name;
    Gtk::Entry *fiscal_code;
    Gtk::Entry *health_code;
    Gtk::Entry *street;
    Gtk::Entry *civic;
    Gtk::Entry *zip_code;
    Gtk::Entry *city;
    Gtk::Entry *country;
    Gtk::Entry *birth_city;
    Gtk::Entry *birth_country;
    Gtk::ComboBoxText *add_birth_day;
    Gtk::ComboBoxText *add_birth_month;
    Gtk::ComboBoxText *add_birth_year;

    log->info("[AddPatientDialog] Resetting");

    refBuilder.get_widget("addFirstName", first_name);
    refBuilder.get_widget("addLastName", last_name);
    refBuilder.get_widget("addFiscalCode", fiscal_code);
    refBuilder.get_widget("addHealthCode", health_code);
    refBuilder.get_widget("addBirthCity", birth_city);
    refBuilder.get_widget("addBirthCountry", birth_country);
    refBuilder.get_widget("addStreetAddress", street);
    refBuilder.get_widget("addCivic", civic);
    refBuilder.get_widget("addZipCode", zip_code);
    refBuilder.get_widget("addCity", city);
    refBuilder.get_widget("addCountry", country);
    refBuilder.get_widget("addBirthDateDay", add_birth_day);
    refBuilder.get_widget("addBirthDateMonth", add_birth_month);
    refBuilder.get_widget("addBirthDateYear", add_birth_year);

    for (int i = 1; i <= 31; i++)
        add_birth_day->append(Glib::ustring::format(i));
    for (int i = 1; i <= 12; i++)
        add_birth_month->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    for (int i = util::Date::get_current_year(); i >= 1920; i--)
        add_birth_year->append(Glib::ustring::format(i));

    add_birth_day->set_active_text(Glib::ustring::format(util::Date::get_current_day()));
    add_birth_month->set_active_text(Glib::ustring(util::Date::get_current_month() < 10 ? "0" : "").append(
            Glib::ustring::format(util::Date::get_current_month())));
    add_birth_year->set_active_text(Glib::ustring::format(util::Date::get_current_year()));

    first_name->set_text("");
    last_name->set_text("");
    fiscal_code->set_text("");
    health_code->set_text("");
    street->set_text("");
    civic->set_text("");
    zip_code->set_text("");
    city->set_text("");
    country->set_text("");
    birth_city->set_text("");
    birth_country->set_text("");
}

