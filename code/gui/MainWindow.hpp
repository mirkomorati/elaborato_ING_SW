//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_MAINWINDOW_HPP
#define ELABORATO_ING_SW_MAINWINDOW_HPP

#include "Window.hpp"

namespace mm {
    class MainWindow : public Window {
        WindowName next;
    public:
        MainWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;
    };
}

#endif //ELABORATO_ING_SW_MAINWINDOW_HPP
