//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include <gtkmm/entry.h>
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
    };
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
