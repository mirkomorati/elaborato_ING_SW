//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_REFBUILDER_HPP
#define ELABORATO_ING_SW_REFBUILDER_HPP

#include <gtkmm-3.0/gtkmm.h>

namespace mm {
    class RefBuilder {
    public:
        static RefBuilder &get_instance();

        template<typename T>
        void get_widget(const Glib::ustring &name, T *widget) {
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
