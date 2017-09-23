//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP

#include "../controller/SelectDateByDialog.hpp"
#include "Dialog.hpp"
#include "../controller/AddPatientDialog.hpp"

namespace mm {
    namespace controller {
        class AddPatientDialog;
    }
    namespace view {
        class AddPatientDialog : public view::Dialog {
        public:
            AddPatientDialog();

            virtual ~AddPatientDialog();

            void set_ok_handler(controller::Dialog *controller, void (controller::Dialog::*handler)(void)) override;

            void set_cancel_handler(controller::Dialog *controller, void (controller::Dialog::*handler)(void)) override;

            void set_select_date_handler(controller::AddPatientDialog *controller,
                                         void (controller::AddPatientDialog::*handler)(void));

            void set_add_birth_date(util::Date date);

        private:
            Gtk::Entry *first_name;
            Gtk::Entry *last_name;
            Gtk::Entry *fiscal_code;
            Gtk::Entry *health_code;
            Gtk::Entry *street;
            Gtk::Entry *civic;
            Gtk::Entry *zip_code;
            Gtk::Entry *city;
            Gtk::Entry *country;
            Gtk::Entry *birth_city;
            Gtk::Entry *birth_country;
            Gtk::ComboBoxText *combo_year;
            Gtk::ComboBoxText *combo_day;
            Gtk::ComboBoxText *combo_month;
            Gtk::Button *ok_button;
            Gtk::Button *cancel_button;

            std::vector<sigc::connection> connections;

            void reset_view();
        };
    }
}

#endif //ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP
