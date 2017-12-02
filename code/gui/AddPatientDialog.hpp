//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include "Dialog.hpp"

namespace mm {
    class AddPatientDialog : public Dialog {
    public:
        AddPatientDialog();

        void show() override;

        bool isActive() override;

        virtual ~AddPatientDialog();

        void reset() override;

    private:

        void dispose() override;

        void birthDateChanged();

        void okHandler();

        void cancelHandler();

        void entryTextChanged(const Glib::ustring &text, int *pos, Gtk::Entry *entry);

        bool is_active;

        Gtk::Button *ok_button;
        Gtk::Button *cancel_button;

        Gtk::Entry *first_name;
        Gtk::Entry *last_name;
        Gtk::Entry *fiscal_code;
        Gtk::Entry *street;
        Gtk::Entry *civic;
        Gtk::Entry *zip_code;
        Gtk::Entry *city;
        Gtk::Entry *country;
        Gtk::Entry *birth_city;
        Gtk::Entry *birth_country;
        Gtk::ComboBoxText *add_birth_day;
        Gtk::ComboBoxText *add_birth_month;
        Gtk::ComboBoxText *add_birth_year;
    };
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
