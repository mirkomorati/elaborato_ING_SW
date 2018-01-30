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
#include <spdlog/spdlog.h>
#include "CustomWidgets.hpp"
#include "../../utils/stringUtils.hpp"

mm::view::PrescriptionExpander::PrescriptionExpander(const mm::model::Prescription &prescription) :
        drugColumns(),
        drugListStore(Gtk::ListStore::create(drugColumns)),
        id(prescription.get_prescription_id()) {

    expirationDate = {Gtk::Label("<b>Data di Scadenza:</b>"), Gtk::Label("")};
    prescriptionID = {Gtk::Label("<b>ID:</b>"), Gtk::Label("")};
    issueDate = {Gtk::Label("<b>Data di Emissione:</b>"), Gtk::Label("")};

    labelBox = Gtk::HBox(false, 5);
    used = Gtk::CheckButton("Usata");

    // content objects

    contentBox = Gtk::HBox(false, 5);
    detailsFrame = Gtk::Frame();
    interactionLabel = Gtk::Label();
    drugFrame = Gtk::Frame();

    drugTreeView.set_model(drugListStore);
    /*
    expirationDate = {new Gtk::Label("<b>Data di Scadenza:</b>"), new Gtk::Label("")};
    prescriptionID = {new Gtk::Label("<b>ID:</b>"), new Gtk::Label("")};
    issueDate = {new Gtk::Label("<b>Data di Emissione:</b>"), new Gtk::Label("")};

    labelBox = new Gtk::HBox(false, 5);
    used = new Gtk::CheckButton("Usata");

    // content objects
    contentBox = new Gtk::HBox(false, 5);
    detailsFrame = new Gtk::Frame();
    interactionLabel = new Gtk::Label();
    drugFrame = new Gtk::Frame();
    drugTreeView = Gtk::manage(Gtk::TreeView();
*/

    //-------------------Label-------------------//
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
    labelBox.pack_start(used, true, true);
    used.set_sensitive(false);
    if (prescription.is_used()) used.set_active(true);

    labelBox.set_margin_top(5);
    labelBox.set_margin_bottom(5);

    set_label_widget(labelBox);

    drugFrame.set_label("Farmaci");
    drugFrame.add(drugTreeView);

    drugTreeView.set_hexpand(false);
    drugTreeView.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

    drugTreeView.append_column("Nome", drugColumns.name);
    drugTreeView.append_column("Forma Farmaceutica", drugColumns.pharmaceutical_form);
    drugTreeView.append_column("ATC", drugColumns.ATC_classification);
    drugTreeView.append_column("Controindicazioni", drugColumns.contraindications);
    drugTreeView.append_column("Principi Attivi", drugColumns.active_principles);
    drugTreeView.append_column("Prezzo", drugColumns.price);

    std::stringstream interactionStringStream;
    auto negativeInteractionsVector = util::str::split(prescription.get_negative_interactions(), ';');
    for (auto it = negativeInteractionsVector.begin(); it != negativeInteractionsVector.end();) {
        interactionStringStream << *it;
        if (++it != negativeInteractionsVector.end())
            interactionStringStream << '\n';
    }

    interactionLabel.set_text(interactionStringStream.str().empty() ? "Nessuna" : interactionStringStream.str());
    interactionLabel.set_margin_top(5);
    interactionLabel.set_margin_left(5);
    interactionLabel.set_margin_right(5);
    interactionLabel.set_margin_bottom(5);

    for (int i = 0; i < 6; i++) {
        drugTreeView.get_column(i)->set_min_width(100);
        drugTreeView.get_column(i)->set_resizable(true);
        drugTreeView.get_column_cell_renderer(i)->property_xalign().set_value(0);
        drugTreeView.get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        drugTreeView.get_column_cell_renderer(i)->set_property("ellipsize", Pango::EllipsizeMode::ELLIPSIZE_END);
    }

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

    issueDateText = issueDate.second.get_text();

    //-------------------content-------------------//
    detailsFrame.add(interactionLabel);
    detailsFrame.set_label("Possibili interazioni");
    detailsFrame.set_vexpand(true);
    detailsFrame.set_valign(Gtk::Align::ALIGN_START);

    contentBox.pack_start(drugFrame, true, true);
    contentBox.pack_start(detailsFrame, false, false);
    contentBox.set_hexpand(true);
    contentBox.set_halign(Gtk::Align::ALIGN_START);

    add(contentBox);

    show_all();
}

/*
mm::view::PrescriptionExpander::PrescriptionExpander(const mm::model::Prescription &prescription) :
        prescriptionID("<b>ID:</b>", ""),
        issueDate("<b>Data di Emissione:</b>", ""),
        expirationDate("<b>Data di Scadenza:</b>", ""),
        labelBox(false, 5),
        contentBox(false, 5),
        used("Usata"),
        drugListStore(Gtk::ListStore::create(model::Drug::drugTreeModel)),
        id(prescription.get_prescription_id()) {

    //-------------------Label-------------------//
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
    labelBox.pack_start(used, true, true);
    used.set_sensitive(false);
    if (prescription.is_used()) used.set_active(true);


    labelBox.set_margin_top(5);
    labelBox.set_margin_bottom(5);

    set_label_widget(labelBox);
    add(contentBox);

    //-------------------content-------------------//
    detailsFrame.add(interactionLabel);
    detailsFrame.set_label("Possibili interazioni");
    detailsFrame.set_vexpand(true);
    detailsFrame.set_valign(Gtk::Align::ALIGN_START);

    contentBox.pack_start(drugFrame, true, true);
    contentBox.pack_start(detailsFrame, false, false);
    contentBox.set_hexpand(true);
    contentBox.set_halign(Gtk::Align::ALIGN_START);

    drugFrame.set_label("Farmaci");
    drugFrame.add(drugTreeView);
    drugTreeView.set_hexpand(false);
    drugTreeView.remove_all_columns();
    drugTreeView.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

    drugTreeView.append_column("Nome", model::Drug::drugTreeModel.name);
    drugTreeView.append_column("Forma Farmaceutica", model::Drug::drugTreeModel.pharmaceutical_form);
    drugTreeView.append_column("ATC", model::Drug::drugTreeModel.ATC_classification);
    drugTreeView.append_column("Controindicazioni", model::Drug::drugTreeModel.contraindications);
    drugTreeView.append_column("Principi Attivi", model::Drug::drugTreeModel.active_principles);
    drugTreeView.append_column("Prezzo", model::Drug::drugTreeModel.price);

    std::stringstream interactionStringStream;
    auto negativeInteractionsVector = util::str::split(prescription.get_negative_interactions(), ';');
    for (auto it = negativeInteractionsVector.begin(); it != negativeInteractionsVector.end();) {
        interactionStringStream << *it;
        if (++it != negativeInteractionsVector.end())
            interactionStringStream << '\n';
    }

    interactionLabel.set_text(interactionStringStream.str().empty() ? "Nessuna" : interactionStringStream.str());
    interactionLabel.set_margin_top(5);
    interactionLabel.set_margin_left(5);
    interactionLabel.set_margin_right(5);
    interactionLabel.set_margin_bottom(5);

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
*/

int mm::view::PrescriptionExpander::getID() const {
    return id;
}

mm::view::PrescriptionExpander::~PrescriptionExpander() {
    spdlog::get("out")->debug("PrescriptionExpander::~PrescriptionExpander called destructor");
    /*
    delete expirationDate.first;
    delete expirationDate.second;
    delete prescriptionID.first;
    delete prescriptionID.second;
    delete issueDate.first;
    delete issueDate.second;

    delete labelBox;
    delete used;

    delete contentBox;
    delete detailsFrame;
    delete interactionLabel;
    delete drugFrame;
    delete drugTreeView;
    */
}

Glib::ustring mm::view::PrescriptionExpander::get_name() const {
    return Glib::ustring("PrescriptionExpander");
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

mm::view::PatientExpander::PatientExpander(const mm::model::Patient &patient, const mm::model::Drug &drug,
                                           const mm::util::Date &start, const mm::util::Date &end) :
        labelBox(false, 10),
        name("<b>Nome:</b>", ""),
        lastName("<b>Cognome:</b>", ""),
        fiscalCode("<b>Codice Fiscale</b>", ""),
        prescriptionListStore(Gtk::ListStore::create(model::Prescription::prescriptionTreeModel)) {


    name.first.set_use_markup(true);
    lastName.first.set_use_markup(true);
    fiscalCode.first.set_use_markup(true);

    labelBox.pack_start(name.first, true, true);
    labelBox.pack_start(name.second, true, true);
    labelBox.pack_start(lastName.first, true, true);
    labelBox.pack_start(lastName.second, true, true);
    labelBox.pack_start(fiscalCode.first, true, true);
    labelBox.pack_start(fiscalCode.second, true, true);

    name.second.set_text(patient.get_first_name());
    lastName.second.set_text(patient.get_last_name());
    fiscalCode.second.set_text(patient.get_fiscal_code());

    set_label_widget(labelBox);

    // content
    prescriptionFrame.set_label("Prescrizioni");

    add(prescriptionFrame);

    // prescription treeView setting
    prescriptionTreeView.append_column("ID prescrizione",
                                       mm::model::Prescription::prescriptionTreeModel.prescription_id);
    prescriptionTreeView.append_column("Data di emissione", mm::model::Prescription::prescriptionTreeModel.issue_date);
    prescriptionTreeView.append_column("Data di scadenza", mm::model::Prescription::prescriptionTreeModel.expire_date);
    prescriptionTreeView.append_column("Usata", mm::model::Prescription::prescriptionTreeModel.used);

    for (int i = 0; i < 4; i++) {
        prescriptionTreeView.get_column(i)->set_min_width(100);
        prescriptionTreeView.get_column(i)->set_resizable(true);
        prescriptionTreeView.get_column_cell_renderer(i)->property_xalign().set_value(0);
        prescriptionTreeView.get_column_cell_renderer(i)->set_property("ellipsize-set", (gboolean) 1);
        prescriptionTreeView.get_column_cell_renderer(i)->set_property("ellipsize",
                                                                       Pango::EllipsizeMode::ELLIPSIZE_END);
    }

    std::vector<mm::model::Prescription> filteredPrescriptions;

    for (auto &p : patient.get_prescriptions()) {
        auto drugs = p.get_drugs();
        if (std::find(drugs.begin(), drugs.end(), drug) != drugs.end()) {
            if (end > start) {
                util::Date issue;
                issue.set_from_str(p.get_issue_date());
                if (issue > end and issue < start) filteredPrescriptions.emplace_back(p);

            } else {
                filteredPrescriptions.emplace_back(p);
            }
        }
    }

    prescriptionTreeView.set_model(prescriptionListStore);

    prescriptionListStore->clear();
    auto row = *prescriptionListStore->append();

    for (size_t i = 0; i < filteredPrescriptions.size(); i++) {
        row[model::Prescription::prescriptionTreeModel.prescription_id] = std::to_string(
                filteredPrescriptions[i].get_prescription_id());
        row[model::Prescription::prescriptionTreeModel.issue_date] = filteredPrescriptions[i].get_issue_date();
        row[model::Prescription::prescriptionTreeModel.expire_date] = filteredPrescriptions[i].get_expire_date();
        row[model::Prescription::prescriptionTreeModel.used] = filteredPrescriptions[i].is_used() ? "Si" : "No";

        if (i < filteredPrescriptions.size() - 1)
            row = *(prescriptionListStore->append()++);
    }

    prescriptionFrame.add(prescriptionTreeView);

    show_all();
}
