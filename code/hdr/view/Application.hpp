//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_PATIENTVIEW_HPP
#define ELABORATO_ING_SW_PATIENTVIEW_HPP

#include <gtkmm/toolbutton.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/grid.h>
#include "../controller/Application.hpp"
#include "../model/Patient.hpp"
#include "../model/Prescription.hpp"
#include "../interfaces/IObserver.hpp"
#include "../model/Application.hpp"

namespace mm {
    namespace controller {
        class Application;
    }
    namespace view {

        class Application : public IObserver {
        public:
            explicit Application(controller::Application &c);

            void show_patient_details();

            void set_patient_tree();

            void set_prescription_tree();

            void set_drug_tree();

            void unselect_patient();

            void unselect_prescription();

            void unselect_drug();


            void update() override;



        private:
            shared_ptr<model::Application> model;
        };
    }
}


#endif //ELABORATO_ING_SW_PATIENTVIEW_HPP
