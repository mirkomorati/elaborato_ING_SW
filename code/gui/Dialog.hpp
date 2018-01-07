//
// Created by Noè Murr on 30/11/2017.
//

#ifndef ELABORATO_ING_SW_DIALOG_HPP
#define ELABORATO_ING_SW_DIALOG_HPP

#include <sigc++/trackable.h>
#include <gtkmm/dialog.h>
#include "../interfaces/ISubject.hpp"

namespace mm {
    class Dialog : public ISubject, public sigc::trackable {
    protected:
        bool onDelete(GdkEventAny *any_event) {
            dispose();
            return true;
        }
    public:
        virtual void show() = 0; // it shows the dialog
        virtual void dispose() = 0; // close the dialog
        virtual bool isActive() = 0; // it return false if the dialog may be destructed
        virtual void reset() = 0; // reset dialog content
    };
}


#endif //ELABORATO_ING_SW_DIALOG_HPP
