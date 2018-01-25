//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <array>
#include <gtkmm/grid.h>
#include <gtkmm/listbox.h>
#include "Dialog.hpp"
#include "Widgets.hpp"
#include "view/CustomWidgets.hpp"

namespace mm {
    class AddPrescriptionDialog : public Dialog {
    public:
        AddPrescriptionDialog();

        void show() override;

        void dispose() override;

        bool isActive() override;

        void reset() override;

        ~AddPrescriptionDialog() override;

    private:
        bool is_active;

        void okHandler();

        void cancelHandler();

        void drugAddHandler();

        Gtk::Button *ok_button;
        Gtk::Button *cancel_button;

        Gtk::Button *drugAdd;
        Gtk::Button *interactionAdd;

        Gtk::ComboBoxText *drugComboBox;
        Gtk::ComboBoxText *monthComboBox;
        Gtk::ComboBoxText *interactionComboBox1;
        Gtk::ComboBoxText *interactionComboBox2;

        Gtk::ListBox *interactionListBox;
        Gtk::ListBox *drugListBox;
        std::vector<std::unique_ptr<mm::view::DrugEntry>> drugEntries;
        std::vector<std::unique_ptr<mm::view::InteractionEntry>> interactionEntries;

        void drugRemoveHandler(mm::view::DrugEntry *removed);

        void interactionRemoveHandler(mm::view::InteractionEntry *removed);

        void initDrugComboBox();

        void initMonthComboBox();

        void monthValidityChanged();

        void interactionAddHandler();
    };

}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
