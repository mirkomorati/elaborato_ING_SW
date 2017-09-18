//
// Created by Noè Murr on 14/09/2017.
//

#include "../../hdr/controller/Register.hpp"

mm::controller::Register *mm::controller::Register::instance = nullptr;

mm::controller::Main &mm::controller::Register::get_main() {
    return main;
}

mm::controller::Login &mm::controller::Register::get_login() {
    return login;
}

mm::controller::Patient &mm::controller::Register::get_patient() {
    return patient;
}

mm::controller::Register::Register() {}

mm::controller::Register &mm::controller::Register::get_instance() {
    if (instance == nullptr) instance = new Register();

    return *instance;
}

mm::controller::SelectDateDialog &mm::controller::Register::get_select_date_dialog() {
    return select_date_dialog;
}

mm::controller::AddPatientDialog &mm::controller::Register::get_add_patient_dialog() {
    return add_patient_dialog;
}

mm::controller::AddPrescriptionDialog &mm::controller::Register::get_add_prescription_dialog() {
    return add_prescription_dialog;
}

mm::controller::SelectDateByDialog &mm::controller::Register::get_select_date_by_dialog() {
    return select_date_by_dialog;
}
