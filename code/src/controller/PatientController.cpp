//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/controller/PatientController.hpp"

void mm::PatientController::set_view(PatientView *view) {
    this->patient_view = view;
}

void mm::PatientController::set_parent(mm::MainController *parent) {
    this->parent = parent;
}

void mm::PatientController::add_patient_handler() {
    std::cout << "Add Patient Click" << std::endl;
}

void mm::PatientController::remove_patient_handler() {
    std::cout << "Remove Patient Click" << std::endl;
}

void mm::PatientController::edit_patient_handler() {
    std::cout << "Edit Patient Click" << std::endl;
}
