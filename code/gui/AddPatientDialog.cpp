//
// Created by Mirko Morati on 30/11/17.
//

#include <spdlog/spdlog.h>
#include "AddPatientDialog.hpp"
#include "RefBuilder.hpp"
#include "../model/Patient.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"
#include "../utils/Date.hpp"

mm::AddPatientDialog::AddPatientDialog() :
        first_name("addFirstName"),
        last_name("addLastName"),
        fiscal_code("addFiscalCode"),
        street("addStreetAddress"),
        civic("addCivic"),
        zip_code("addZipCode"),
        city("addCity"),
        country("addCountry"),
        birth_city("addBirthCity"),
        birth_country("addBirthCountry") {
    is_active = true;
    auto refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addBirthDateDay", add_birth_day);
    refBuilder.get_widget("addBirthDateMonth", add_birth_month);
    refBuilder.get_widget("addBirthDateYear", add_birth_year);

    refBuilder.get_widget("addPatientOk", ok_button);
    refBuilder.get_widget("addPatientCancel", cancel_button);

    reset();

    add_birth_day->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    add_birth_month->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    add_birth_year->signal_changed().connect(sigc::mem_fun(this, &mm::AddPatientDialog::birthDateChanged));
    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::cancelHandler));
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

    util::Date date;
    int day, month, year;

    try {
        day = std::stoi(add_birth_day->get_active_text().c_str());
        month = std::stoi(add_birth_month->get_active_text().c_str());
        year = std::stoi(add_birth_year->get_active_text().c_str());
    } catch (...) {
        // todo in init phase there is no month available set the default value
        day = 1;
        month = 1;
        year = 2000;
    }

    date = util::Date(day, month, year);

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

void mm::AddPatientDialog::entryTextChanged(const Glib::ustring &text, int *pos, Gtk::Entry *entry) {
    Glib::ustring n_text = entry->get_text().uppercase();
    entry->set_text(n_text);
}

void mm::AddPatientDialog::okHandler() {
    mm::model::Patient patient;
    stringstream address;
    stringstream birth_address;
    stringstream birth_date;
    auto refBuilder = RefBuilder::get_instance();

    patient.set_first_name(first_name.entry->get_text());
    patient.set_last_name(last_name.entry->get_text());
    patient.set_fiscal_code(fiscal_code.entry->get_text());
    birth_date << add_birth_day->get_active_text().c_str() << "/"
               << add_birth_month->get_active_text().c_str() << "/"
               << add_birth_year->get_active_text().c_str();
    patient.set_birth_date(birth_date.str());

    address << street.entry->get_text() << " "
            << civic.entry->get_text() << ", "
            << zip_code.entry->get_text() << ", "
            << city.entry->get_text() << ", "
            << country.entry->get_text();

    birth_address << birth_city.entry->get_text() << ", "
                  << birth_country.entry->get_text();

    patient.set_address(address.str());
    patient.set_doctor_id(mm::model::authentication::Login::get_instance().regional_id);
    patient.set_birth_place(birth_address.str());

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
    auto refBuilder = RefBuilder::get_instance();

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

    first_name.entry->set_text("");
    last_name.entry->set_text("");
    fiscal_code.entry->set_text("");
    street.entry->set_text("");
    civic.entry->set_text("");
    zip_code.entry->set_text("");
    city.entry->set_text("");
    country.entry->set_text("");
    birth_city.entry->set_text("");
    birth_country.entry->set_text("");
}

mm::AddPatientDialog::~AddPatientDialog() {
    // todo gestire il reset dei campi.
}
