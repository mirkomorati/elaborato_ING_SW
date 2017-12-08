//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_MAINWINDOW_HPP
#define ELABORATO_ING_SW_MAINWINDOW_HPP

#include "Window.hpp"
#include "Dialog.hpp"
#include "view/CustomWidgets.hpp"
#include <list>
#include <gtkmm/liststore.h>
#include <gtkmm/treeviewcolumn.h>

namespace mm {
    class MainWindow : public Window, public IObserver {

        enum DetailStack {
            PRESCRIPTION,
            DRUG,
            NONE
        };

        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;
        std::vector<std::unique_ptr<view::PrescriptionExpander>> prescriptionsExp;

        //-------------------List stores-------------------//
        Glib::RefPtr<Gtk::ListStore> patientListStore;

    public:
        MainWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

    private:
        //-------------------init functions-------------------//

        void initHandlers();

        void initTreeView();

        //-------------------signal handlers-------------------//
        void onAddPatientClicked();

        void onAddPrescriptionClicked();

        void onSelectedPatient(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *);

        void onRemovePatientClicked();

        void onLogout();

        void onAboutClicked();


        //-------------------graphics updates-------------------//

        void updatePatientTreeView();

        void updatePrescriptionView();

        void updatePatientDetailsView();

        void updateDetailStack(DetailStack page);

    };
}

#endif //ELABORATO_ING_SW_MAINWINDOW_HPP
