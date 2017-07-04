//
// Created by Noè Murr on 03/07/2017.
//

#include "../../hdr/view/PatientView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::PatientView::PatientView(mm::PatientController *controller) : controller(controller) {
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("addPatient", add_patient);
    refBuilder.get_widget("removePatient", remove_patient);
    refBuilder.get_widget("editPatient", edit_patient);

    add_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::add_patient_handler));
    remove_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::remove_patient_handler));
    edit_patient->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::PatientController::edit_patient_handler));
}
