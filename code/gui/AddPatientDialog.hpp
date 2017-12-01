//
// Created by Mirko Morati on 30/11/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include "Dialog.hpp"

namespace mm {
    class AddPatientDialog : public Dialog {
    public:
        AddPatientDialog();

        void show() override;

        bool isActive() override;

    private:
        void dispose() override;

    public:
        void reset() override;

    private:

        void birthDateChanged();

        void okHandler();

        void cancelHandler();

        bool is_active;
    };
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
