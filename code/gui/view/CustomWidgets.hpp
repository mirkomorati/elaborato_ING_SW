//
// Created by Noè Murr on 08/12/2017.
//

#ifndef ELABORATO_ING_SW_CUSTOMWIDGETS_HPP
#define ELABORATO_ING_SW_CUSTOMWIDGETS_HPP

#include <gtkmm/expander.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include "../../model/Prescription.hpp"

namespace mm::view {
    class PrescriptionExpander : public Gtk::Expander {
        // label objects
        std::pair<Gtk::Label, Gtk::Label> expirationDate;
        std::pair<Gtk::Label, Gtk::Label> prescriptionID;
        std::pair<Gtk::Label, Gtk::Label> issueDate;
        Gtk::Button gotoButton;
        Gtk::Box labelBox;

        // content objects
        Gtk::Box contentBox;
        Gtk::Frame detailsFrame;
        Gtk::Grid detailsGrid;
        Gtk::Label interactionsLabel;
        Gtk::TextView interactionsTextView;
        Glib::RefPtr<Gtk::TextBuffer> interactionsBuffer;
        Gtk::ScrolledWindow interactionsScrolled;
        Gtk::CheckButton used;
        Gtk::TreeView drugTreeView;
        Glib::RefPtr<Gtk::ListStore> drugListStore;

        const int id;

    public:
        PrescriptionExpander(const mm::model::Prescription &prescription);

        PrescriptionExpander() = delete;

        PrescriptionExpander &operator=(PrescriptionExpander &) = delete;

        int getID() const;
    };
}


#endif //ELABORATO_ING_SW_CUSTOMWIDGETS_HPP