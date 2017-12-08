//
// Created by Noè Murr on 08/12/2017.
//

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/textview.h>
#include "CustomWidgets.hpp"

mm::view::PrescriptionExpander::PrescriptionExpander(const mm::model::Prescription &prescription) :
        prescriptionID("<b>ID:</b>", ""),
        issueDate("<b>Data di Emissione:</b>", ""),
        expirationDate("<b>Data di Scadenza:</b>", ""),
        gotoButton("Vai"),
        labelBox(Gtk::ORIENTATION_HORIZONTAL, 5 /* spacing */),
        contentBox(Gtk::ORIENTATION_HORIZONTAL, 5 /* spacing */),
        interactionsLabel("Possibili Interazioni"),
        used("Usata"),
        drugListStore(Gtk::ListStore::create(model::Drug::drugTreeModel)),
        id(prescription.get_prescription_id()) {

    //-------------------Label-------------------//
    labelBox.set_homogeneous();

    prescriptionID.first.set_use_markup(true);
    issueDate.first.set_use_markup(true);
    expirationDate.first.set_use_markup(true);

    prescriptionID.second.set_label(std::to_string(prescription.get_prescription_id()));
    issueDate.second.set_label(prescription.get_issue_date());
    expirationDate.second.set_label(prescription.get_expire_date());

    labelBox.pack_start(prescriptionID.first, true, true);
    labelBox.pack_start(prescriptionID.second, true, true);
    labelBox.pack_start(issueDate.first, true, true);
    labelBox.pack_start(issueDate.second, true, true);
    labelBox.pack_start(expirationDate.first, true, true);
    labelBox.pack_start(expirationDate.second, true, true);
    labelBox.pack_end(gotoButton, false, false);

    set_label_widget(labelBox);

    //-------------------content-------------------//
    interactionsScrolled.add(interactionsTextView);
    detailsFrame.add(detailsGrid);
    detailsGrid.attach(interactionsLabel, 0, 0, 1, 1);
    detailsGrid.attach(interactionsScrolled, 0, 1, 2, 1);
    detailsGrid.attach(used, 1, 2, 1, 1);
    used.set_active(false);
    interactionsTextView.set_buffer(interactionsBuffer);
    interactionsBuffer->set_text(prescription.get_negative_interactions());

    contentBox.pack_start(detailsFrame, true, true);

    contentBox.pack_start(drugTreeView, true, true);

    drugTreeView.remove_all_columns();

    drugTreeView.append_column("Nome", model::Drug::drugTreeModel.name);
    drugTreeView.append_column("Forma Farmaceutica", model::Drug::drugTreeModel.pharmaceutical_form);
    drugTreeView.append_column("Classificazione ATC", model::Drug::drugTreeModel.ATC_classification);
    drugTreeView.append_column("Controindicazioni", model::Drug::drugTreeModel.contraindications);
    drugTreeView.append_column("Principi Attivi", model::Drug::drugTreeModel.active_principles);
    drugTreeView.append_column("Prezzo", model::Drug::drugTreeModel.price);

    for (int i = 0; i < 6; i++) {
        drugTreeView.get_column(i)->set_min_width(100);
        drugTreeView.get_column(i)->set_resizable(true);
        drugTreeView.get_column_cell_renderer(i)->property_xalign().set_value(0);
        drugTreeView.get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        drugTreeView.get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    drugTreeView.set_model(drugListStore);
    // updating the view for the first time
    drugTreeView.set_model(drugListStore);

    auto drugs = prescription.get_drugs();

    drugListStore->clear();
    auto row = *drugListStore->append();

    for (size_t i = 0; i < drugs.size(); i++) {
        row[model::Drug::drugTreeModel.name] = drugs[i].get_name();
        row[model::Drug::drugTreeModel.pharmaceutical_form] = drugs[i].get_pharmaceutical_form();
        row[model::Drug::drugTreeModel.ATC_classification] = drugs[i].get_ATC_classification();
        row[model::Drug::drugTreeModel.contraindications] = drugs[i].get_contraindications_as_string();
        row[model::Drug::drugTreeModel.active_principles] = drugs[i].get_active_principles_as_string();
        row[model::Drug::drugTreeModel.price] = drugs[i].get_price_as_string();

        if (i < drugs.size() - 1)
            row = *(drugListStore->append()++);
    }
}

int mm::view::PrescriptionExpander::getID() const {
    return id;
}
