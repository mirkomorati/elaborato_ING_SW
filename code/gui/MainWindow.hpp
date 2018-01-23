//
// Created by Noè Murr on 23/12/2017.
//

#ifndef ELABORATO_ING_SW_MAIN_WINDOW_HPP
#define ELABORATO_ING_SW_MAIN_WINDOW_HPP

#include <glib.h>
#include <gtkmm/widget.h>
#include <array>
#include "Window.hpp"
#include "Dialog.hpp"

namespace mm {
    class MainWindow : public Window, public IObserver {

        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;

        std::array<std::unique_ptr<Window>, 2> tabWindows;

    public:
        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

        MainWindow();

    private:
        //-------------------init functions-------------------//

        void initHandlers();

        //-------------------signal handlers-------------------//
        void onLogout();

        void onAboutClicked();
    };
}


#endif //ELABORATO_ING_SW_MAIN_WINDOW_HPP
