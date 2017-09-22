//
// Created by Mirko Morati on 18/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOGVIEW_HPP
#define ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOGVIEW_HPP


#include "Dialog.hpp"

namespace mm {
    namespace view {
        class AddPrescriptionDialog : public view::Dialog {
        public:
            AddPrescriptionDialog();

            void set_ok_handler(controller::Dialog *controller, void (controller::Dialog::*handler)(void)) override;

            void set_cancel_handler(controller::Dialog *controller, void (controller::Dialog::*handler)(void)) override;

            void set_combo_box(std::vector<std::string> text);

            void reset_view();

        private:
            Gtk::Button *ok_button;
            Gtk::Button *cancel_button;
            Gtk::Entry *add_patient_id;
            Gtk::Entry *add_prescription_id;
            Gtk::Entry *add_issue_date;
            Gtk::Entry *add_expire_date;
            Gtk::TextView *add_negative_interactions;
            Gtk::ComboBoxText *add_drug_ids[5];

        };
    }
}

#endif //ELABORATO_ING_SW_ADDPRESCRIPTIONDIALOGVIEW_HPP
