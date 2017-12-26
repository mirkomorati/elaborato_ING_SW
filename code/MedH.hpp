//
// Created by Noè Murr on 22/09/2017.
//

#ifndef ELABORATO_ING_SW_MEDH_HPP
#define ELABORATO_ING_SW_MEDH_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "interfaces/IObserver.hpp"
#include "gui/Window.hpp"

namespace mm {
    class MedH : IObserver {
        std::unique_ptr<Window> window;

        bool init();

    public:
        MedH(int argc, char **argv);

        Glib::RefPtr<Gtk::Application> app;

        /// lancia il main loop del programma.
        int run();


    private:
        void update() override;
    };
}


#endif //ELABORATO_ING_SW_MEDH_HPP
