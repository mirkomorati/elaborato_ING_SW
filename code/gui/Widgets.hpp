//
// Created by Mirko Morati on 02/12/17.
//

#ifndef ELABORATO_ING_SW_WIDGETS_HPP
#define ELABORATO_ING_SW_WIDGETS_HPP


#include <gtkmm/entry.h>

namespace mm {
    struct EntryController : public sigc::trackable {
        EntryController() = delete;

        EntryController(const std::string &entryId);

        void entryTextChanged(const Glib::ustring &text, int *pos);

        Gtk::Entry *entry;
    };

    struct DateController : public sigc::trackable {
        // todo usare lo stesso metodo della EntryController
    };
}


#endif //ELABORATO_ING_SW_WIDGETS_HPP
