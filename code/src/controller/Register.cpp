//
// Created by Noè Murr on 14/09/2017.
//

#include "../../hdr/controller/Register.hpp"

mm::controller::Register *mm::controller::Register::instance = nullptr;

mm::controller::Main &mm::controller::Register::getMain_controller() {
    return main_controller;
}

mm::controller::Login &mm::controller::Register::getLogin_controller() {
    return login_controller;
}

mm::controller::Patient &mm::controller::Register::getPatient_controller() {
    return patient_controller;
}

mm::controller::Register::Register() {}

mm::controller::Register &mm::controller::Register::get_instance() {
    if (instance == nullptr) instance = new Register();

    return *instance;
}
