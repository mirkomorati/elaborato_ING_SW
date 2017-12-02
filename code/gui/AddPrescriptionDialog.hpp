//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include "Dialog.hpp"

namespace mm {
    class AddPrescriptionDialog : public Dialog {
    public:
        AddPrescriptionDialog();

        void show() override;

        void dispose() override;

        bool isActive() override;

        void reset() override;

    private:
        bool is_active;

        void okHandler();

        void cancelHandler();

        Gtk::Button *ok_button;
        Gtk::Button *cancel_button;

        Gtk::Entry *addPatientId;
        Gtk::Entry *addPrescriptionId;
        Gtk::ComboBoxText *add_issue_day;
        Gtk::ComboBoxText *add_issue_month;
        Gtk::ComboBoxText *add_issue_year;
        Gtk::ComboBoxText *add_expire_day;
        Gtk::ComboBoxText *add_expire_month;
        Gtk::ComboBoxText *add_expire_year;
    };
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
