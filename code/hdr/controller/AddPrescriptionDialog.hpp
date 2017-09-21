//
// Created by Mirko Morati on 18/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP


#include "Dialog.hpp"
#include "Application.hpp"
#include "../view/AddPrescriptionDialog.hpp"

namespace mm {
    namespace controller {
        class AddPrescriptionDialog : public controller::Dialog {
        public:
            AddPrescriptionDialog();

            ~AddPrescriptionDialog();

            void ok_handler() override;

            void cancel_handler() override;

            void set_view() override;

            void free();

            static Dialog *create();

            void show_dialog() override;

        private:
            view::AddPrescriptionDialog *view;
        };
    }
}


#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP