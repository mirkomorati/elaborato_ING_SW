//
// Created by Noè Murr on 23/12/2017.
//

#ifndef ELABORATO_ING_SW_MAIN_WINDOW_HPP
#define ELABORATO_ING_SW_MAIN_WINDOW_HPP

#include <glib.h>
#include <gtkmm/widget.h>
#include "Window.hpp"
#include "Dialog.hpp"

namespace mm {
    class MainWindow : public Window, public IObserver {

        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;

        std::unique_ptr<Window> activeTabWindow;

    public:
        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

    private:
        //-------------------init functions-------------------//

        void initHandlers();

        //-------------------signal handlers-------------------//
        void onLogout();

        void onAboutClicked();

        void onPageSwitch(Gtk::Widget *page, guint page_number);

    };
}


#endif //ELABORATO_ING_SW_MAIN_WINDOW_HPP
