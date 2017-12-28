//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP

#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <array>
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

        std::array<Gtk::ComboBoxText *, 5> drugCombos;
        DateController issueDate;
        DateController expireDate;
    };
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
