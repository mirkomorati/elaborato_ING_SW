//
// Created by Mirko Morati on 04/06/17.
//

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include "../controller/MainController.hpp"
#include <mutex>

namespace mm {
    class MainController;

    class MainWindow {
    public:
        MainWindow(std::string window_id, MainController *controller);

        virtual ~MainWindow();

        Gtk::ApplicationWindow &getMainWindow();

        void onLoginButtonClicked();

        void loginUpdate(int doctor_id);

    private:
        Gtk::ApplicationWindow *window;
        Gtk::Button *login_button;
        MainController *controller;
        std::mutex mutex;

    protected:
        //Signal handlers

        //Child widgets
        Glib::RefPtr<Gtk::Builder> refBuilder;

        void patientView(int doctor_id);
    };
}

#endif //_MAINWINDOW_H