//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_LOGIN_HPP
#define ELABORATO_ING_SW_LOGIN_HPP

#include "../DBMaster.hpp"
#include "../interfaces/ISubject.hpp"
#include <vector>
#include <tuple>

namespace mm {
    namespace model {
        namespace authentication {

            /**
             * @brief classe che rappresenta la una sessione di login
             *
             * Un oggetto di questo tipo può essere creato in modo solo dalla funzione check_login
             * se il login è già stato effettuato si può usare la funzione get_instance per accedere ai dati relativi
             * all'utente connesso, per sapere se la sessione è valida si può usare la funzione isLog.
             */
            struct Login : public ISerializable, public ISubject {
                friend bool check_login(std::string usr, std::string psw);

                bool is_changed;
                std::string user_name;
                std::string password;
                int regional_id;

                map<string, Serialized> serialize() const override;

                void unserialize(map<string, Serialized> map) override;

                string get_table_name() const override;

                vector<string> get_primary_key() const override;

                /**
                 * @brief Ritorna un istanza di tipo Login
                 *
                 * Se il login non è stato creato mediante la funzione check_login
                 * L'oggetto ritornato sarà non valido e la funzione isLog su di esso ritornerà false
                 *
                 * @return un oggetto di tipo Login
                 */
                static Login &get_instance();

                /**
                 * @brief Permette di effettuare il logout rendendo l'oggetto in uno stato non valido
                 */
                void logout();

                /**
                 * @brief permette di controllare se l'oggetto è in uno stato valido o meno
                 *
                 * @return true se l'utente è connesso, false altrimenti
                 */
                bool isLog() const;


            private:
                explicit Login();

                Login(const Login &other) = default;

                Login &operator=(const Login &other);
            };

            /**
             * @brief Si occupa di porre in uno stato valido l'oggetto del singleton Login.
             *
             * Se usr e psw corrispondono ad una coppia nome utente e password nel database inizializza Login e
             * ritorna true
             *
             * @param usr stringa contenente lo username
             * @param psw stringa contenente la password
             * @return true in caso l'utente sia trovato false altrimenti
             */
            bool check_login(std::string usr, std::string psw);
        }
    }
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
