//
// Created by Noè Murr on 14/09/2017.
//

#include "../../hdr/controller/Register.hpp"

const mm::controller::Main &mm::controller::Register::getMain_controller() const {
    return main_controller;
}

const mm::controller::Login &mm::controller::Register::getLogin_controller() const {
    return login_controller;
}

const mm::controller::Patient &mm::controller::Register::getPatient_controller() const {
    return patient_controller;
}
