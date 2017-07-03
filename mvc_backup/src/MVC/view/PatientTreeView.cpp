//
// Created by Noè Murr on 02/07/2017.
//

#include "../../../../code/hdr/MVC/view/PatientTreeView.hpp"


mm::PatientTreeView::PatientTreeView(mm::MainView *parent, Glib::RefPtr <Gtk::Builder> refBuilder, int doctor_id) :
        parent(parent), doctor_id(doctor_id) {
    refBuilder->get_widget("patientTreeView", patient_tree_view);

    auto refListStore = Gtk::ListStore::create(patient_cols);
    Gtk::TreeModel::Row row = *(refListStore->append());
}

PatientCols &mm::PatientTreeView::get_cols() {
    return cols;
}
