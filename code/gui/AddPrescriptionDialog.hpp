//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP

#include "Dialog.hpp"

namespace mm {
    class AddPrescriptionDialog : public Dialog {
    public:
        AddPrescriptionDialog();

        void show() override;

        void dispose() override;

        bool isActive() override;

    private:
        bool is_active;

        void okHandler();

        void cancelHandler();
    };
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOG_HPP
