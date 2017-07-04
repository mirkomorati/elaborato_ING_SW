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

void mm::PatientView::set_patient_tree_model(PatientTreeModel &patient_tree_model,
                                             Glib::RefPtr<Gtk::ListStore> patient_list_store) {
    Gtk::TreeView *patient_tree_view;

    RefBuilder::get_instance().get_widget("patientTreeView", patient_tree_view);

    patient_tree_view->append_column("Nome", patient_tree_model.first_name);
    patient_tree_view->append_column("Cognome", patient_tree_model.last_name);
    patient_tree_view->append_column("Cod. Fiscale", patient_tree_model.fiscal_code);
    patient_tree_view->set_model(patient_list_store);

}

void mm::PatientView::add_patient_show_dialog() {
    Gtk::Dialog *add_patient_dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog",
                                          add_patient_dialog);
    add_patient_dialog->show();
}
