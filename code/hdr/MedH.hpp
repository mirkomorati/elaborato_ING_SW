//
// Created by Noè Murr on 22/09/2017.
//

#ifndef ELABORATO_ING_SW_MEDH_HPP
#define ELABORATO_ING_SW_MEDH_HPP


#include "controller/Main.hpp"
#include "view/Main.hpp"

namespace mm {
    /**
     * rappresenta l'applicazione stessa, si occupa di gestire tutti i controller e le view.
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

        int run();
    };
}


#endif //ELABORATO_ING_SW_MEDH_HPP
