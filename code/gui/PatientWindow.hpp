//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_PATIENT_WINDOW_HPP
#define ELABORATO_ING_SW_PATIENT_WINDOW_HPP

#include "Window.hpp"
#include "Dialog.hpp"
#include "view/CustomWidgets.hpp"
#include "../utils/Date.hpp"
#include "Widgets.hpp"
#include <list>
#include <gtkmm/liststore.h>
#include <gtkmm/treeviewcolumn.h>

namespace mm {
    class PatientWindow : public Window, public IObserver {

        WindowName next;
        std::list<std::unique_ptr<Dialog>> dialogList;
        std::vector<std::unique_ptr<view::PrescriptionExpander>> prescriptionsExp;

        //-------------------List stores-------------------//
        Glib::RefPtr<Gtk::ListStore> patientListStore;

        //-------------------Filter utilities-------------------//
        bool filterOn;
        util::Date filterStartDate;
        util::Date filterEndDate;
        DateController customFilterFromDateController;
        DateController customFilterToDateController;

    public:
        PatientWindow();

        bool init() override;

        WindowName getName() const override;

        WindowName getNextWindow() const override;

        void update() override;

        void update(unsigned int what) override;

        ~PatientWindow() override;

    private:
        //-------------------init functions-------------------//

        void initHandlers();

        void initTreeView();

        void initFilters();

        //-------------------signal handlers-------------------//
        void onAddPatientClicked();

        void onAddPrescriptionClicked();

        void onSelectedPatient(const Gtk::TreeModel::Path &, Gtk::TreeViewColumn *);

        void onRemovePatientClicked();

        void onRemovePrescriptionClicked();

        void onSwitchActivate();

        void onFilterYearChanged();

        void onFilterQuarterChanged();

        void onFilterMonthChanged();

        void onFilterCustomChanged();

        int sortPrescriptionList(Gtk::ListBoxRow *row1, Gtk::ListBoxRow *row2, Gtk::SortType sortType);

        bool onFilterClose(GdkEventButton *buttonEvent);

        bool onFilterOpened(GdkEventButton *buttonEvent);

        //-------------------graphics updates-------------------//

        void updatePatientTreeView();

        void updatePrescriptionView();

        void updatePatientDetailsView();

        void onFilterSemesterChanged();

        void sortByPrescriptionHandler();
    };
}

#endif //ELABORATO_ING_SW_PATIENT_WINDOW_HPP
