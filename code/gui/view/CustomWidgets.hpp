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
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/textview.h>
#include <gtkmm/hvpaned.h>
#include <gtkmm/listboxrow.h>
#include "../../model/Prescription.hpp"
#include "../../utils/Date.hpp"

namespace mm::view {
    class PrescriptionExpander : public Gtk::Expander {
        // label objects
        std::pair<Gtk::Label, Gtk::Label> expirationDate;
        std::pair<Gtk::Label, Gtk::Label> prescriptionID;
        std::pair<Gtk::Label, Gtk::Label> issueDate;
        Gtk::Button gotoButton;
        Gtk::Box labelBox;

        // content objects
        Gtk::HPaned contentPaned;
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

        bool operator<(const PrescriptionExpander &r) const {
            return mm::util::Date(this->issueDate.second.get_text()) < mm::util::Date(r.issueDate.second.get_text());
        }

        inline bool operator>(const PrescriptionExpander &rhs) const { return rhs < *this; }

        int getID() const;
    };

    class PatientExpander : public Gtk::Expander {
    public:
        PatientExpander();
    };

    class DrugEntry : public Gtk::ListBoxRow {
    public:
        DrugEntry() = delete;

        DrugEntry(const Glib::ustring &drug);

        sigc::signal<void, mm::view::DrugEntry *> signal_removed();

        const string get_drugName() const;

        const string get_drugForm() const;

    protected:
        sigc::signal<void, mm::view::DrugEntry *> remove;

    private:
        Gtk::Entry entry;
        Gtk::Button button;
        Gtk::Grid grid;
        Glib::ustring drug;

        void removeHandler();
    };

    class InteractionEntry : public Gtk::ListBoxRow {
    public:
        InteractionEntry() = delete;

        InteractionEntry(const Glib::ustring &drug1, const Glib::ustring &drug2);

        sigc::signal<void, mm::view::InteractionEntry *> signal_removed();

        const string &get_drug1() const;

        const string &get_drug2() const;

    protected:
        sigc::signal<void, mm::view::InteractionEntry *> remove;

    private:
        Gtk::Entry entry;
        Gtk::Button button;
        Gtk::Grid grid;
        string drug1;
        string drug2;

        void removeHandler();
    };
}


#endif //ELABORATO_ING_SW_CUSTOMWIDGETS_HPP
