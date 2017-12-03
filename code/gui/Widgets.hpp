//
// Created by Mirko Morati on 02/12/17.
//

#ifndef ELABORATO_ING_SW_WIDGETS_HPP
#define ELABORATO_ING_SW_WIDGETS_HPP


#include <gtkmm/entry.h>

namespace mm {
    struct EntryController {
        EntryController();

        EntryController(Gtk::Entry *entry);

        void entryTextChanged(const Glib::ustring &text, int *pos);

        Gtk::Entry *entry;
    };

    struct DateController {

    };
}


#endif //ELABORATO_ING_SW_WIDGETS_HPP
