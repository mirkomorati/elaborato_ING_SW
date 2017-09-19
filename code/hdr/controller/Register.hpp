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

            // istanza della classe.
            static Register *instance;

            // costruttore
            Register();

            ~Register() = default;

        public:
            Main &get_main();

            Login &get_login();

            Patient &get_patient();

            Register(const Register &other) = delete;

            const Register &operator=(const Register &old) = delete;

            static Register &get_instance();
        };
    }
}


#endif //ELABORATO_ING_SW_REGISTER_HPP
