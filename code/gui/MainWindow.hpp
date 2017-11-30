//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_MAINWINDOW_HPP
#define ELABORATO_ING_SW_MAINWINDOW_HPP

#include "Window.hpp"
#include "Dialog.hpp"
#include <list>

namespace mm {
    class MainWindow : public Window, public IObserver {
        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;
    public:
        MainWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

    private:

    };
}

#endif //ELABORATO_ING_SW_MAINWINDOW_HPP
