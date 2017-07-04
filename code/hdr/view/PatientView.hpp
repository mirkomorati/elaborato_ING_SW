//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTVIEW_HPP
#define ELABORATO_ING_SW_PATIENTVIEW_HPP

#include <gtkmm/toolbutton.h>
#include "../controller/PatientController.hpp"

namespace mm {
    class PatientController;

    class PatientView {
    public:
        PatientView(PatientController *controller);

    private:
        PatientController *controller;

        Gtk::ToolButton *add_patient;
        Gtk::ToolButton *edit_patient;
        Gtk::ToolButton *remove_patient;
    };
}


#endif //ELABORATO_ING_SW_PATIENTVIEW_HPP
