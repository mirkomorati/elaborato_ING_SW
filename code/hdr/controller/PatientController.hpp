//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
#define ELABORATO_ING_SW_PATIENTCONTROLLER_HPP

#include "../view/PatientView.hpp"
#include "MainController.hpp"

namespace mm {
    class PatientView;

    class MainController;

    class PatientController {
    public:
        void set_view(PatientView *patient_view);

        void set_parent(mm::MainController *parent);

        void add_patient_handler();

        void remove_patient_handler();

        void edit_patient_handler();

    private:
        PatientView *patient_view;
        MainController *parent;
    };
}

#endif //ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
