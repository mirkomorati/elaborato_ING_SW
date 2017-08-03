//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTTREEVIEW_HPP
#define ELABORATO_ING_SW_PATIENTTREEVIEW_HPP

#include "MainView.hpp"

namespace mm {
    class PatientTreeView {
    public:
        PatientTreeView(MainView *parent, Glib::RefPtr<Gtk::Builder> refBuilder, int doctor_id);

        PatientCols &get_cols();

    private:
        MainView *parent;
        int doctor_id;

        Gtk::TreeView *patient_tree_view;
    };
}


#endif //ELABORATO_ING_SW_PATIENTTREEVIEW_HPP
