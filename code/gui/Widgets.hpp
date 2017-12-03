//
// Created by Mirko Morati on 02/12/17.
//

#ifndef ELABORATO_ING_SW_WIDGETS_HPP
#define ELABORATO_ING_SW_WIDGETS_HPP


#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include "../utils/Date.hpp"

namespace mm {
    struct EntryController : public sigc::trackable {
        EntryController() = delete;

        EntryController(const std::string &entryId);

        void entryTextChanged(const Glib::ustring &, int *);

        // inline per aumentare la leggibilità ma non a scapito delle prestazioni;
        inline void reset() { entry->set_text(""); }

        inline std::string text() { return entry->get_text(); }

        Gtk::Entry *entry;
    };

    struct DateController : public sigc::trackable {
        DateController() = delete;

        DateController(const std::string &dayId, const std::string &monthId, const std::string &yearId);

        void onDateChanged();

        void reset();

        inline std::string getDateAsString() {
            return fmt::format("{}/{}/{}", day->get_active_text().c_str(), month->get_active_text().c_str(),
                               year->get_active_text().c_str());
        }

        util::Date getDate();

        Gtk::ComboBoxText *day;
        Gtk::ComboBoxText *month;
        Gtk::ComboBoxText *year;
    };
}


#endif //ELABORATO_ING_SW_WIDGETS_HPP
