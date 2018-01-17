//
// Created by Noè Murr on 08/12/2017.
//

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/textview.h>
#include <iostream>
#include <gtkmm/stock.h>
#include <gtkmm/listbox.h>
#include <fmt/format.h>
#include "CustomWidgets.hpp"
#include "../../utils/stringUtils.hpp"

mm::view::PrescriptionExpander::PrescriptionExpander(const mm::model::Prescription &prescription) :
        prescriptionID("<b>ID:</b>", ""),
        issueDate("<b>Data di Emissione:</b>", ""),
        expirationDate("<b>Data di Scadenza:</b>", ""),
        gotoButton("Vai"),
        labelBox(Gtk::ORIENTATION_HORIZONTAL, 5 /* spacing */),
        interactionsLabel("Possibili Interazioni"),
        interactionsBuffer(Gtk::TextBuffer::create()),
        used("Usata"),
        drugListStore(Gtk::ListStore::create(model::Drug::drugTreeModel)),
        id(prescription.get_prescription_id()) {

    //-------------------Label-------------------//
    labelBox.set_homogeneous();

    prescriptionID.first.set_use_markup(true);
    issueDate.first.set_use_markup(true);
    expirationDate.first.set_use_markup(true);

    prescriptionID.first.set_width_chars(5);
    prescriptionID.second.set_width_chars(5);

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
    add(contentPaned);

    //-------------------content-------------------//
    interactionsScrolled.add(interactionsTextView);
    detailsFrame.add(detailsGrid);
    detailsGrid.attach(interactionsLabel, 0, 0, 1, 1);
    detailsGrid.attach(interactionsScrolled, 0, 1, 2, 1);
    detailsGrid.attach(used, 1, 2, 1, 1);

    used.set_sensitive(false);
    if (prescription.is_used()) used.set_active(true);

    interactionsTextView.set_buffer(interactionsBuffer);
    interactionsBuffer->set_text(prescription.get_negative_interactions());

    contentPaned.pack1(detailsFrame, true, true);
    contentPaned.pack2(drugTreeView, true, true);

    drugTreeView.remove_all_columns();
    drugTreeView.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

    drugTreeView.append_column("Nome", model::Drug::drugTreeModel.name);
    drugTreeView.append_column("Forma Farmaceutica", model::Drug::drugTreeModel.pharmaceutical_form);
    drugTreeView.append_column("ATC", model::Drug::drugTreeModel.ATC_classification);
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

    show_all();
}

int mm::view::PrescriptionExpander::getID() const {
    return id;
}


mm::view::DrugEntry::DrugEntry(const Glib::ustring &drug) : drug(drug) {
    entry.set_text(drug.c_str());
    entry.set_editable(false);
    entry.set_hexpand(true);
    button.set_image_from_icon_name("list-remove", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    button.signal_clicked().connect(sigc::mem_fun(this, &mm::view::DrugEntry::removeHandler));

    grid.attach(entry, 0, 0, 1, 1);
    grid.attach(button, 1, 0, 1, 1);

    add(grid);
    set_halign(Gtk::Align::ALIGN_FILL);
    set_hexpand(true);
    show_all();
}

void mm::view::DrugEntry::removeHandler() {
    remove.emit(this);
}

sigc::signal<void, mm::view::DrugEntry *> mm::view::DrugEntry::signal_removed() {
    return remove;
}

const string mm::view::DrugEntry::get_drugName() const {
    string str = mm::util::str::split(drug.c_str(), '-', true)[0];
    return str.substr(0, str.size() - 1);
}

const string mm::view::DrugEntry::get_drugForm() const {
    string str = mm::util::str::split(drug.c_str(), '-', true)[1];
    return str.substr(1, str.size());
}

mm::view::InteractionEntry::InteractionEntry(const Glib::ustring &drug1, const Glib::ustring &drug2) : drug1(
        drug1.c_str()), drug2(drug2.c_str()) {
    entry.set_text(fmt::format("{} <-> {}", drug1.c_str(), drug2.c_str()));
    entry.set_editable(false);
    entry.set_hexpand(true);
    button.set_image_from_icon_name("list-remove", Gtk::BuiltinIconSize::ICON_SIZE_BUTTON);
    button.signal_clicked().connect(sigc::mem_fun(this, &mm::view::InteractionEntry::removeHandler));

    grid.attach(entry, 0, 0, 1, 1);
    grid.attach(button, 1, 0, 1, 1);

    add(grid);
    set_halign(Gtk::Align::ALIGN_FILL);
    set_hexpand(true);
    show_all();
}

void mm::view::InteractionEntry::removeHandler() {
    remove.emit(this);
}

sigc::signal<void, mm::view::InteractionEntry *> mm::view::InteractionEntry::signal_removed() {
    return remove;
}

const string &mm::view::InteractionEntry::get_drug1() const {
    return drug1;
}

const string &mm::view::InteractionEntry::get_drug2() const {
    return drug2;
}
