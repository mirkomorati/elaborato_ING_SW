//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOG_HPP

#include "../view/SelectDateDialog.hpp"
#include "../time_utilities/Date.hpp"
#include "AddPatientDialog.hpp"

namespace mm {
    namespace view {
        class SelectDateDialog;
    }

    namespace controller {
        class AddPatientDialog;

        class SelectDateDialog : public controller::Dialog {
        public:

            ~SelectDateDialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

            // todo: questa funzione deve essere polimorfica. Qua il parent serve
            void set_parent(AddPatientDialog *parent);

            util::Date get_date();

        private:
            controller::AddPatientDialog *parent;
            util::Date date;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
