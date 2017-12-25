//
// Created by Noè Murr on 04/12/2017.
//

#ifndef ELABORATO_ING_SW_ABOUTDIALOG_HPP
#define ELABORATO_ING_SW_ABOUTDIALOG_HPP

#include "Dialog.hpp"

namespace mm {
    class AboutDialog : public Dialog {
        bool active;

        void dispose() override;

    public:
        AboutDialog();

        void show() override;

        bool isActive() override;

        void reset() override;

        void onResponse(int id);
    };
}


#endif //ELABORATO_ING_SW_ABOUTDIALOG_HPP
