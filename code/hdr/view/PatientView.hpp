//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTVIEW_HPP
#define ELABORATO_ING_SW_PATIENTVIEW_HPP

#include "../controller/PatientController.hpp"

namespace mm {
    class PatientController;

    class PatientView {
    public:
        PatientView(PatientController &controller);

    private:
        PatientController &controller;
    };
}


#endif //ELABORATO_ING_SW_PATIENTVIEW_HPP
