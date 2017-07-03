//
// Created by Mirko Morati on 04/06/17.
//

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>
#include "../controller/MainController.hpp"
#include "PatientTreeView.hpp"
#include "LoginView.hpp"
#include <mutex>

namespace mm {
    class MainController;

    class LoginView;

    class MainView {
    public:
        MainView(std::string window_id, MainController *controller);

        virtual ~MainView();

        Gtk::ApplicationWindow &getMainWindow();

        void onLoginButtonClicked();

        void login_update(int doctor_id);

        MainController *get_controller();

    private:
        // mutex of views
        std::mutex login_mutex;

        // gtk objects
        Gtk::ApplicationWindow *window;

        // views
        LoginView *login_view;
        PatientTreeView *patient_tree_view;

        // other.
        Gtk::Button *login_button;
        MainController *controller;
        std::mutex mutex;

    protected:
        //Signal handlers

        //Child widgets
        Glib::RefPtr<Gtk::Builder> refBuilder;

        void patient_view(int doctor_id);
    };
}

#endif //_MAINWINDOW_H