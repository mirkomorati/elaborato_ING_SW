//
// Created by Noè Murr on 04/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTTREEMODEL_HPP
#define ELABORATO_ING_SW_PATIENTTREEMODEL_HPP

#include <gtkmm/treemodelcolumn.h>

namespace mm {
    struct PatientTreeModel : Gtk::TreeModelColumnRecord {
        PatientTreeModel();

        Gtk::TreeModelColumn<Glib::ustring> first_name;
        Gtk::TreeModelColumn<Glib::ustring> last_name;
        Gtk::TreeModelColumn<Glib::ustring> fiscal_code;
        Gtk::TreeModelColumn<Glib::ustring> health_code;
        Gtk::TreeModelColumn<Glib::ustring> birth_date;
        Gtk::TreeModelColumn<Glib::ustring> birth_place;
        Gtk::TreeModelColumn<Glib::ustring> address;
        Gtk::TreeModelColumn<Glib::ustring> risk_factors;

    };
}


#endif //ELABORATO_ING_SW_PATIENTTREEMODEL_HPP
