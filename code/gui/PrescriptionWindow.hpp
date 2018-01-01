//
// Created by Mirko Morati on 31/12/17.
//

#ifndef ELABORATO_ING_SW_PRESCRIPTIONWINDOW_HPP
#define ELABORATO_ING_SW_PRESCRIPTIONWINDOW_HPP

#include <gtkmm/liststore.h>
#include "Window.hpp"

namespace mm {
    class PrescriptionWindow : public mm::Window, public IObserver {
    public:
        PrescriptionWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

    private:
        WindowName next;
        Glib::RefPtr<Gtk::ListStore> prescriptionListStore;

        void initTreeView();

        void updatePrescriptionTreeView();

        int onSortCompareByDate(const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b);
    };
}


#endif //ELABORATO_ING_SW_PRESCRIPTIONWINDOW_HPP
