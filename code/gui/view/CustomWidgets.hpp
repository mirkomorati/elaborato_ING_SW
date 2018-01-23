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
#include "../../model/Patient.hpp"

namespace mm::view {
    class PrescriptionExpander : public Gtk::Expander {
        // label objects
        std::pair<Gtk::Label, Gtk::Label> expirationDate;
        std::pair<Gtk::Label, Gtk::Label> prescriptionID;
        std::pair<Gtk::Label, Gtk::Label> issueDate;
        Gtk::HBox labelBox;
        Gtk::CheckButton used;

        // content objects
        Gtk::HBox contentBox;
        Gtk::Frame detailsFrame;
        Gtk::Label interactionLabel;
        Gtk::Frame drugFrame;
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
        // label widgets
        Gtk::HBox labelBox;
        std::pair<Gtk::Label, Gtk::Label> name;
        std::pair<Gtk::Label, Gtk::Label> lastName;
        std::pair<Gtk::Label, Gtk::Label> fiscalCode;

        // content widgets
        Gtk::Frame prescriptionFrame;
        Gtk::TreeView prescriptionTreeView;
        Glib::RefPtr<Gtk::ListStore> prescriptionListStore;

    public:
        PatientExpander(const mm::model::Patient &patient, const mm::model::Drug &drug,
                        const mm::util::Date &start = mm::util::Date::get_current_date(),
                        const mm::util::Date &end = mm::util::Date::get_current_date());
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
