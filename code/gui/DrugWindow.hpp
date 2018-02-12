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

        void initHandlers();

        void initTreeView();

        void updateDrugTreeView();

        void updateDrugDetailsView();

        void updatePatientView();

        void onSelectedDrug(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *);

        void initDrugFilter();

        void initQuantityFilter();

    private:
        mm::WindowName next;

        bool filterDrugOn;
        bool filterQuantityOn;

        util::Date filterStartDate;
        util::Date filterEndDate;

        util::Date quantityStartDate;
        util::Date quantityEndDate;

        Glib::RefPtr<Gtk::ListStore> drugListStore;

        std::vector<std::unique_ptr<view::PatientExpander>> patientExp;

        bool onFilterClose(GdkEventButton *buttonEvent);

        bool onFilterOpened(GdkEventButton *buttonEvent);

        void onSwitchActivate();

        void onFilterYearChanged();

        void onFilterMonthChanged();

        void onQuantityYearChanged();

        void onQuantitySemesterChanged();

        void onQuantityQuarterChanged();

        void onQuantityMonthChanged();

        void updateTotalDrug();
    };
}

#endif //ELABORATO_ING_SW_DRUGWINDOW_HPP
