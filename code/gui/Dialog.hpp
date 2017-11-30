//
// Created by Noè Murr on 30/11/2017.
//

#ifndef ELABORATO_ING_SW_DIALOG_HPP
#define ELABORATO_ING_SW_DIALOG_HPP

namespace mm {
    class Dialog : public ISubject {
    public:
        virtual void show() = 0; // it shows the dialog
        virtual bool isActive() = 0; // it return false if the dialog may be destructed
    };
}


#endif //ELABORATO_ING_SW_DIALOG_HPP
