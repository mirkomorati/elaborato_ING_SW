//
// Created by Mirko Morati on 30/11/17.
//

#include <spdlog/spdlog.h>
#include "AddPatientDialog.hpp"
#include "RefBuilder.hpp"
#include "../model/Patient.hpp"
#include "../DBMaster.hpp"
#include "../model/Authentication.hpp"

#define UPDATE_NOTHING 0

mm::AddPatientDialog::AddPatientDialog()
        : is_active(true), first_name("addFirstName"), last_name("addLastName"), fiscal_code("addFiscalCode"),
          street("addStreetAddress"), civic("addCivic"), zip_code("addZipCode"), city("addCity"), country("addCountry"),
          birth_city("addBirthCity"), birth_country("addBirthCountry"), riskFactors("addRiskFactors"),
          birthDate("addBirthDateDay", "addBirthDateMonth", "addBirthDateYear") {

    auto refBuilder = RefBuilder::get_instance();
    Gtk::Dialog *dialog;

    refBuilder.get_widget("addPatientOk", ok_button);
    refBuilder.get_widget("addPatientCancel", cancel_button);
    refBuilder.get_widget("addPatientDialog", dialog);

    reset();

    ok_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::okHandler));
    cancel_button->signal_clicked().connect(sigc::mem_fun(this, &mm::AddPatientDialog::cancelHandler));
    dialog->signal_delete_event().connect(sigc::mem_fun(this, &mm::AddPatientDialog::onDelete));
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

void mm::AddPatientDialog::okHandler() {
    mm::model::Patient patient;
    std::string address;
    std::string birth_address;
    std::string birth_date;
    auto refBuilder = RefBuilder::get_instance();

    patient.set_first_name(first_name.text());
    patient.set_last_name(last_name.text());
    patient.set_fiscal_code(fiscal_code.text());
    birth_date = birthDate.getDateAsString();
    patient.set_birth_date(birth_date);

    if (street.text().empty() or civic.text().empty() or zip_code.text().empty() or city.text().empty()
        or birth_city.text().empty() or birth_country.text().empty()) {
        Gtk::Label *error;
        refBuilder.get_widget("addPatientError", error);
        error->set_visible(true);
        return;
    }


    address = fmt::format("{} {}, {}, {}, {}", street.text(), civic.text(), zip_code.text(), city.text(),
                          country.text());

    birth_address = fmt::format("{}, {}", birth_city.text(), birth_country.text());

    patient.set_address(address);
    patient.set_doctor_id(mm::model::authentication::Login::get_instance().regional_id);
    patient.set_birth_place(birth_address);

    if (patient.is_valid()) {
        if (DBMaster::get_instance().exists(patient.get_table_name(),
                                            patient.get_primary_key()[0],
                                            patient.get_fiscal_code())) {
            Gtk::Label *error;
            refBuilder.get_widget("addPatientError", error);
            error->set_visible(true);
            return;
        }
        DBMaster::get_instance().add_to_db(patient);
        dispose(true);
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
    dispose(false);
}

void mm::AddPatientDialog::dispose(bool update) {
    Gtk::Dialog *dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog", dialog);
    dialog->hide();
    is_active = false;
    if (update)
        this->notify();
    else
        this->notify(UPDATE_NOTHING);
}

void mm::AddPatientDialog::reset() {
    birthDate.reset();
    first_name.reset();
    last_name.reset();
    fiscal_code.reset();
    street.reset();
    civic.reset();
    zip_code.reset();
    city.reset();
    country.reset();
    birth_city.reset();
    birth_country.reset();
}
