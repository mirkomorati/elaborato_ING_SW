//
// Created by Noè Murr on 30/11/2017.
//

#ifndef ELABORATO_ING_SW_DIALOG_HPP
#define ELABORATO_ING_SW_DIALOG_HPP

#include <sigc++/trackable.h>
#include "../interfaces/ISubject.hpp"

namespace mm {
    class Dialog : public ISubject, public sigc::trackable {
    public:
        virtual void show() = 0; // it shows the dialog
        virtual void dispose() = 0; // close the dialog
        virtual bool isActive() = 0; // it return false if the dialog may be destructed
    };
}


#endif //ELABORATO_ING_SW_DIALOG_HPP
