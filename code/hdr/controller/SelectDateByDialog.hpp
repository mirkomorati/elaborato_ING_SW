//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP

#include "../view/SelectDateByDialog.hpp"
#include "../time_utilities/DateBy.hpp"
#include "Application.hpp"

namespace mm {
    namespace controller {
        class Application;

        class SelectDateByDialog : public controller::Dialog {
        public:
            SelectDateByDialog();

            ~SelectDateByDialog();

            void ok_handler() override;

            void cancel_handler() override;

            void set_view() override;

            void set_parent(Application *parent);

            util::DateBy get_date();

            void free();

            static Dialog *create();

            void show_dialog() override;

        private:
            controller::Application *parent;
            view::SelectDateByDialog *view;
            util::DateBy date_by;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
