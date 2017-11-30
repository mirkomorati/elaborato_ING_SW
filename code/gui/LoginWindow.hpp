//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_LOGINWINDOW_HPP
#define ELABORATO_ING_SW_LOGINWINDOW_HPP

#include "Window.hpp"

namespace mm {
    class LoginWindow : public Window {
        WindowName next;
    public:
        LoginWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

    private:

        void onLoginButtonClicked();

        bool onKeyPressed(GdkEventKey *event);
    };
}

#endif //ELABORATO_ING_SW_LOGINWINDOW_HPP
