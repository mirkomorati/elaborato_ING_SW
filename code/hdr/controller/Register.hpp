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
            Main main_controller;
            Login login_controller;
            Patient patient_controller;
            // todo da aggiungere i controller.

        public:
            const Main &getMain_controller() const;

            const Login &getLogin_controller() const;

            const Patient &getPatient_controller() const;

            Register() = delete;

        };
    }
}


#endif //ELABORATO_ING_SW_REGISTER_HPP
