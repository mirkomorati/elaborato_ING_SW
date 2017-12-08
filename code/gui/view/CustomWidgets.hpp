//
// Created by Noè Murr on 08/12/2017.
//

#ifndef ELABORATO_ING_SW_CUSTOMWIDGETS_HPP
#define ELABORATO_ING_SW_CUSTOMWIDGETS_HPP

#include <gtkmm/expander.h>
#include "../../model/Prescription.hpp"

namespace mm::view {
    class PrescriptionExpander : public Gtk::Expander {
    public:
        PrescriptionExpander(const mm::model::Prescription &prescription);
    };
}


#endif //ELABORATO_ING_SW_CUSTOMWIDGETS_HPP
