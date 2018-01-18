//
// Created by Noè Murr on 18/01/2018.
//

#ifndef ELABORATO_ING_SW_DRUGWINDOW_HPP
#define ELABORATO_ING_SW_DRUGWINDOW_HPP

#include <gtkmm/liststore.h>
#include "Window.hpp"
#include "view/CustomWidgets.hpp"

namespace mm {
    class DrugWindow : public Window, public IObserver {
    public:
        DrugWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

        void initHandler();

        void initTreeView();

        void initDrugFilter();

        void initQuantityFilter();

    private:
        mm::WindowName next;

        bool filterDrugOn;
        bool fiterQuantityOn;

        Glib::RefPtr<Gtk::ListStore> drugListStore;

        std::vector<std::unique_ptr<view::PatientExpander>> patientExp;
    };
}

#endif //ELABORATO_ING_SW_DRUGWINDOW_HPP
