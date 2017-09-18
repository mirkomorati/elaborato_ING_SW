//
// Created by Noè Murr on 14/09/2017.
//

#ifndef ELABORATO_ING_SW_REGISTER_HPP
#define ELABORATO_ING_SW_REGISTER_HPP

#include "Main.hpp"

namespace mm {
    namespace controller {
        /**
         * Classe che contiene l'insieme di tutti i controller
         */
        class Register {
            // todo da aggiungere i controller.
            Main main;
            Login login;
            Patient patient;
            SelectDateDialog select_date_dialog;
            AddPatientDialog add_patient_dialog;
            AddPrescriptionDialog add_prescription_dialog;
            SelectDateByDialog select_date_by_dialog;

            // istanza della classe.
            static Register *instance;

            // costruttore
            Register();

            ~Register() = default;

        public:
            Main &get_main();

            Login &get_login();

            Patient &get_patient();

            SelectDateDialog &get_select_date_dialog();

            AddPatientDialog &get_add_patient_dialog();

            AddPrescriptionDialog &get_add_prescription_dialog();

            SelectDateByDialog &get_select_date_by_dialog();

            Register(const Register &other) = delete;

            const Register &operator=(const Register &old) = delete;

            static Register &get_instance();
        };
    }
}


#endif //ELABORATO_ING_SW_REGISTER_HPP
