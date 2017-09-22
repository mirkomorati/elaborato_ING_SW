//
// Created by Noè Murr on 14/09/2017.
//

#include "../../hdr/controller/Register.hpp"

mm::controller::Register *mm::controller::Register::instance = nullptr;

mm::controller::Main &mm::controller::Register::get_main() {
    return main;
}

mm::controller::Application &mm::controller::Register::get_patient() {
    return patient;
}

mm::controller::Register::Register() {}

mm::controller::Register &mm::controller::Register::get_instance() {
    if (instance == nullptr) instance = new Register();

    return *instance;
}