//
// Created by Noè Murr on 22/09/2017.
//

#ifndef ELABORATO_ING_SW_MEDH_HPP
#define ELABORATO_ING_SW_MEDH_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "interfaces/IObserver.hpp"
#include "gui/Window.hpp"

namespace mm {
    /**
     * @class MedH MedH.hpp "MedH.hpp"
     * @brief Classe che rappresenta il programma in se.
     *
     * Per utilizzare tutte le funzionalità del programma MedH compresa l'interfaccia
     * sarà necessario semplicemente creare un oggetto di MedH e richiamarne il metodo
     * run.
     *
     * N.B. È possibile avviare più istanze dell'applicazione purché gli id nel config
     * file siano diversi.
     */
    class MedH : IObserver {
        std::unique_ptr<Window> window;
        std::string appID;

        /// metodo che inizializza l'oggetto
        bool init();

    public:
        MedH(int argc, char **argv);

        Glib::RefPtr<Gtk::Application> app;

        /// lancia il main loop del programma.
        int run();

        virtual ~MedH();

    private:
        /// metodo usato dal design pattern Observer
        void update() override;
    };
}


#endif //ELABORATO_ING_SW_MEDH_HPP
