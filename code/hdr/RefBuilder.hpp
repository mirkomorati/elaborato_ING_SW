//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_REFBUILDER_HPP
#define ELABORATO_ING_SW_REFBUILDER_HPP

#include <gtkmm-3.0/gtkmm.h>

namespace mm {
    /**
     * @brief Singleton che si occupa di gestire il Gtk::Builder il quale gestisce la creazione della grafica tramite
     * il codice XML editato con il programma Glade.
     */
    class RefBuilder {
    public:
        static RefBuilder &get_instance();

        /**
         * Ritorna il puntatore all'oggetto Gtk con il nome name.
         * @tparam T tipo dell'oggetto
         * @param name nome dell'oggetto
         * @param widget puntatore all'oggetto.
         */
        template<typename T>
        void get_widget(const Glib::ustring &name, T &widget) {
            refBuilder->get_widget(name, widget);
        }

    private:
        RefBuilder();

    private:
        static RefBuilder *instance;
        Glib::RefPtr<Gtk::Builder> refBuilder;
    };
}


#endif //ELABORATO_ING_SW_REFBUILDER_HPP
