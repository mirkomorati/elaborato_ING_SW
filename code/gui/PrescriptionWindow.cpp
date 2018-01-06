//
// Created by Mirko Morati on 31/12/17.
//

#include <iostream>
#include "PrescriptionWindow.hpp"
#include "../model/Prescription.hpp"
#include "RefBuilder.hpp"
#include "../DBMaster.hpp"
#include "../utils/Date.hpp"
#include "../model/Authentication.hpp"
#include "../model/Doctor.hpp"

mm::PrescriptionWindow::PrescriptionWindow() :
        next(MAIN),
        prescriptionListStore(Gtk::ListStore::create(model::Prescription::prescriptionTreeModel)) {

}

bool mm::PrescriptionWindow::init() {
    initTreeView();

    return true;
}

mm::WindowName mm::PrescriptionWindow::getName() const {
    return PRESCRIPTION;
}

mm::WindowName mm::PrescriptionWindow::getNextWindow() const {
    return next;
}

void mm::PrescriptionWindow::initTreeView() {
    Gtk::TreeView *prescriptionTreeView;

    RefBuilder::get_instance().get_widget("prescriptionTreeView", prescriptionTreeView);

    prescriptionTreeView->remove_all_columns();

    prescriptionTreeView->append_column("Paziente", model::Prescription::prescriptionTreeModel.patient_id);
    prescriptionTreeView->append_column("ID", model::Prescription::prescriptionTreeModel.prescription_id);
    prescriptionTreeView->append_column("Data di Emissione", model::Prescription::prescriptionTreeModel.issue_date);
    prescriptionTreeView->append_column("Data di Scadenza", model::Prescription::prescriptionTreeModel.expire_date);
    prescriptionTreeView->append_column("Farmaci", model::Prescription::prescriptionTreeModel.drug_ids);
    prescriptionTreeView->append_column("Interazioni",
                                        model::Prescription::prescriptionTreeModel.negative_interactions);
    prescriptionTreeView->append_column("Usata", model::Prescription::prescriptionTreeModel.used);

    prescriptionTreeView->set_model(prescriptionListStore);
    prescriptionListStore->set_sort_func(2, sigc::mem_fun(this, &mm::PrescriptionWindow::onSortCompareByDate));
    prescriptionTreeView->get_column(2)->set_sort_column(2);

    prescriptionTreeView->get_column(0)->set_sort_column(0);
    prescriptionTreeView->get_column(0)->set_sort_order(Gtk::SortType::SORT_ASCENDING);

    prescriptionTreeView->get_column(4)->set_sort_column(4);
    prescriptionTreeView->get_column(4)->set_sort_order(Gtk::SortType::SORT_ASCENDING);

    for (int i = 0; i < 7; i++) {
        prescriptionTreeView->get_column_cell_renderer(i)->property_xalign().set_value(0);
        prescriptionTreeView->get_column(i)->set_min_width(100);
        prescriptionTreeView->get_column(i)->set_resizable(true);
        prescriptionTreeView->get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        prescriptionTreeView->get_column_cell_renderer(i)->set_property("ellipsize",
                                                                        Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    updatePrescriptionTreeView();
}

void mm::PrescriptionWindow::updatePrescriptionTreeView() {
    model::Prescription prescription;
    std::vector<model::Prescription> prescriptions;

    try {
        model::Doctor tmp;
        DBMaster::get_instance().extract_from_db(tmp, model::authentication::Login::get_instance().regional_id);
        prescriptions = tmp.get_prescriptions();
    } catch (record_not_found_error &e) {
        throw std::runtime_error("cannot get prescriptions from db...");
    }

    prescriptionListStore->clear();

    auto row = *prescriptionListStore->append();

    for (size_t i = 0; i < prescriptions.size(); i++) {
        row[model::Prescription::prescriptionTreeModel.patient_id] = prescriptions[i].get_patient_id();
        row[model::Prescription::prescriptionTreeModel.prescription_id] = Glib::ustring::format(
                prescriptions[i].get_prescription_id());
        row[model::Prescription::prescriptionTreeModel.issue_date] = prescriptions[i].get_issue_date();
        row[model::Prescription::prescriptionTreeModel.expire_date] = prescriptions[i].get_expire_date();
        row[model::Prescription::prescriptionTreeModel.drug_ids] = prescriptions[i].get_drug_ids_as_string();
        row[model::Prescription::prescriptionTreeModel.negative_interactions] = prescriptions[i].get_negative_interactions();
        row[model::Prescription::prescriptionTreeModel.used] = (prescriptions[i].is_used() ? "si" : "no");

        if (i < prescriptions.size() - 1)
            row = *(prescriptionListStore->append()++);
    }
}

void mm::PrescriptionWindow::update() {
    updatePrescriptionTreeView();
}

int mm::PrescriptionWindow::onSortCompareByDate(const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b) {
    auto aa = mm::util::Date(static_cast<Glib::ustring>((*a)[model::Prescription::prescriptionTreeModel.issue_date]));
    auto bb = mm::util::Date(static_cast<Glib::ustring>((*b)[model::Prescription::prescriptionTreeModel.issue_date]));

    if (aa < bb) {
        return -1;
    } else if (aa > bb) {
        return 1;
    }
    return 0;
}

