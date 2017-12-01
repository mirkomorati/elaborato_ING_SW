//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_MAINWINDOW_HPP
#define ELABORATO_ING_SW_MAINWINDOW_HPP

#include "Window.hpp"
#include "Dialog.hpp"
#include <list>
#include <gtkmm/liststore.h>

namespace mm {
    class MainWindow : public Window, public IObserver {
        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;

        //-------------------List stores-------------------//
        Glib::RefPtr<Gtk::ListStore> patientListStore;
        Glib::RefPtr<Gtk::ListStore> prescriptionListStore;

        //-------------------Communication between handlers-------------------//
        std::string selectedPatient; // todo questa non serve posso ottenerla dalla treeView.

    public:
        MainWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

    private:
        //-------------------signal handlers-------------------//
        void onAddPatientClicked();

        void onAddPrescriptionClicked();

        void onSelectedPatient(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *column);

        //-------------------graphics updates-------------------//

        void updatePatientTreeView();

        void updatePrescritpionTreeView();

    };
}

#endif //ELABORATO_ING_SW_MAINWINDOW_HPP
