//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include "Dialog.hpp"
#include "Widgets.hpp"

namespace mm {
    class AddPatientDialog : public Dialog {
    public:
        AddPatientDialog();

        void show() override;

        bool isActive() override;

        ~AddPatientDialog() override;

        void reset() override;

    private:

        void dispose() override;

        void okHandler();

        void cancelHandler();

        bool is_active;

        Gtk::Button *ok_button;
        Gtk::Button *cancel_button;

        EntryController first_name;
        EntryController last_name;
        EntryController fiscal_code;
        EntryController street;
        EntryController civic;
        EntryController zip_code;
        EntryController city;
        EntryController country;
        EntryController birth_city;
        EntryController birth_country;
        EntryController riskFactors;
        DateController birthDate;
    };
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
