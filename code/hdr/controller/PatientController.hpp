//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
#define ELABORATO_ING_SW_PATIENTCONTROLLER_HPP

#include "../view/PatientView.hpp"

namespace mm {
    class PatientView;

    class PatientController {

        PatientView *view;

    public:
        void set_view(PatientView *view);
    };
}

#endif //ELABORATO_ING_SW_PATIENTCONTROLLER_HPP
