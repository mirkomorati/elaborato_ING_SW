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

    RefBuilder::get_instance().get_widget("patientTreeView", patient_tree_view);

    patient_tree_view->append_column("Nome", patient_tree_model.first_name);
    patient_tree_view->append_column("Cognome", patient_tree_model.last_name);
    patient_tree_view->append_column("Cod. Fiscale", patient_tree_model.fiscal_code);
    patient_tree_view->set_model(patient_list_store);

    patient_tree_view->signal_row_activated().connect(sigc::mem_fun(
        controller, &mm::PatientController::row_selected_handler));
}

void mm::PatientView::add_patient_show_dialog() {
    Gtk::Dialog *add_patient_dialog;
    RefBuilder::get_instance().get_widget("addPatientDialog",
                                          add_patient_dialog);
    add_patient_dialog->show();
}

void mm::PatientView::patient_detail_show(Gtk::TreeModel::Row row,
                                          PatientTreeModel &patient_tree_model) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Label *detail_first_name;
    Gtk::Label *detail_last_name;
    Gtk::Label *detail_fiscal_code;
    Gtk::Label *detail_health_code;
    Gtk::Label *detail_birth_date;
    Gtk::Label *detail_birth_place;
    Gtk::Label *detail_address;

    refBuilder.get_widget("detailFirstName", detail_first_name);
    refBuilder.get_widget("detailLastName", detail_last_name);
    refBuilder.get_widget("detailFiscalCode", detail_fiscal_code);
    refBuilder.get_widget("detailHealthCode", detail_health_code);
    refBuilder.get_widget("detailBirthDate", detail_birth_date);
    refBuilder.get_widget("detailBirthPlace", detail_birth_place);
    refBuilder.get_widget("detailAddress", detail_address);

    detail_first_name->set_label(row[patient_tree_model.first_name]);
    detail_last_name->set_label(row[patient_tree_model.last_name]);
    detail_fiscal_code->set_label(row[patient_tree_model.fiscal_code]);

    //TODO: finire l'implementazione quando sarà finita la classe paziente
}
