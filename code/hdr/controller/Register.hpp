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

            // istanza della classe.
            static Register *instance;

            // costruttore
            Register();

            ~Register() = default;

        public:
            Main &getMain_controller();

            Login &getLogin_controller();

            Patient &getPatient_controller();

            Register(const Register &other) = delete;

            const Register &operator=(const Register &old) = delete;

            static Register &get_instance();
        };
    }
}


#endif //ELABORATO_ING_SW_REGISTER_HPP
