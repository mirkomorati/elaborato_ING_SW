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

        void loginUpdate(int doctor_id);

    private:
        // mutex of views
        std::mutex login_mutex;

        // gtk objects
        Gtk::ApplicationWindow *window;

        // views
        LoginView *login_view;

        // other.
        mm::PatientTreeView patient_tree_view;
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


/*
 * LEGGI QUESTE RIGHE
 * Io ora devo andare e probabilmente metterai le mani sul codice prima di me.
 * Per poter eliminare in sicurezza una view bisogna essere SICURI che non vi siano
 * dei metodi della view che sono stati invocati, lo stesso vale per i controller o per
 * i model. È necessario aggiungere dei mutex che vengano lockati in ogni metodo in modo che
 * il padre di ogni oggetto possa efficacemente eliminarlo.
 *
 * Almeno questa è l'idea che mi è venuta in 10 minuti.
 *
 */

#endif //_MAINWINDOW_H