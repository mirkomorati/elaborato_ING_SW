//
// Created by Mirko Morati on 05/07/17.
//

#ifndef ELABORATO_ING_SW_PRESCRIPTIONTREEMODEL_HPP
#define ELABORATO_ING_SW_PRESCRIPTIONTREEMODEL_HPP

#include <gtkmm/treemodelcolumn.h>

namespace mm {
    struct PrescriptionTreeModel : Gtk::TreeModelColumnRecord {
        PrescriptionTreeModel();

        Gtk::TreeModelColumn<Glib::ustring> patient_id;
        Gtk::TreeModelColumn<Glib::ustring> issue_date;
        Gtk::TreeModelColumn<Glib::ustring> expiry_date;
        Gtk::TreeModelColumn<Glib::ustring> drugs;
        Gtk::TreeModelColumn<Glib::ustring> prescription_id;
        Gtk::TreeModelColumn<Glib::ustring> negative_interactions;
        Gtk::TreeModelColumn<Glib::ustring> used;
        Gtk::TreeModelColumn<Glib::ustring> bill_id;

    };
}


#endif //ELABORATO_ING_SW_PRESCRIPTIONTREEMODEL_HPP
