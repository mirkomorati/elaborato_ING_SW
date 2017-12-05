//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include "Dialog.hpp"
#include "Widgets.hpp"

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

        EntryController addPatientId;
        EntryController addPrescriptionId;
        Gtk::ComboBoxText *addDrugId1;
        Gtk::ComboBoxText *addDrugId2;
        Gtk::ComboBoxText *addDrugId3;
        Gtk::ComboBoxText *addDrugId4;
        Gtk::ComboBoxText *addDrugId5;
        DateController issueDate;
        DateController expireDate;
    };
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
