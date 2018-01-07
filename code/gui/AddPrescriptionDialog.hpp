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
        Gtk::ComboBoxText *drugComboBox;
        Gtk::ListBox *drugListBox;
        std::vector<std::unique_ptr<mm::view::DrugEntry>> drugEntries;
        DateController issueDate;
        DateController expireDate;

        void drugRemoveHandler(mm::view::DrugEntry *removed);

        void init();
    };
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
