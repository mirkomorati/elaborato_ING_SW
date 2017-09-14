//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP

#include "../controller/SelectDateDialog.hpp"
#include "Dialog.hpp"

namespace mm {
    namespace controller {
        class SelectDateDialog;
    }

    namespace view {
        class SelectDateDialog : public view::Dialog {
        public:
            SelectDateDialog();
        };
    }
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
