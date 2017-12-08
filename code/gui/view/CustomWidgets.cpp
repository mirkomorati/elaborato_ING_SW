//
// Created by Noè Murr on 08/12/2017.
//

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "CustomWidgets.hpp"

mm::view::PrescriptionExpander::PrescriptionExpander(const mm::model::Prescription &prescription) {
    Gtk::Box labelBox(Gtk::ORIENTATION_HORIZONTAL, 5 /* spacing */);
    labelBox.set_homogeneous();
    std::pair<Gtk::Label, Gtk::Label> expirationDate;
    std::pair<Gtk::Label, Gtk::Label> prescriptionID;
    std::pair<Gtk::Label, Gtk::Label> issueDate;

    prescriptionID.first.set_use_markup(true);
    prescriptionID.first.set_label("<b>ID:</b>");
    issueDate.first.set_use_markup(true);
    issueDate.first.set_label("<b>Data di Emissione:</b>");
    expirationDate.first.set_use_markup(true);
    expirationDate.first.set_label("<b>Data di Scadenza:</b>");

    prescriptionID.second.set_label(std::to_string(prescription.get_prescription_id()));
    issueDate.second.set_label(prescription.get_issue_date());
    expirationDate.second.set_label(prescription.get_expire_date());


}
