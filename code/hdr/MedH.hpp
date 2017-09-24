//
// Created by Noè Murr on 22/09/2017.
//

#ifndef ELABORATO_ING_SW_MEDH_HPP
#define ELABORATO_ING_SW_MEDH_HPP


#include "controller/Main.hpp"
#include "view/Main.hpp"

namespace mm {
    /**
     * @brief rappresenta l'applicazione stessa, si occupa di creare, inizializzare e gestire tutte i controller e
     * le view che vengono utilizzate durante l'esecuzione del programma.
     *
     * Prima di creare un oggetto di MedH è necessario che sia stata chiamata la funzione statica init, che si occupa
     * di creare un applicazione ed inizializzare tutte le librerie usate.
     */
    class MedH {
        controller::Main main_controller;
        controller::Application app_controller;

        view::Main main_view;
        view::Login login_view;
        view::Application app_view;

    public:
        MedH();

        static void init(int argc, char **argv);

        static Glib::RefPtr<Gtk::Application> app;

        /// l'ancia il main loop del programma.
        int run();
    };
}


#endif //ELABORATO_ING_SW_MEDH_HPP
