//
// Created by Noè Murr on 29/11/2017.
//

#ifndef ELABORATO_ING_SW_WINDOW_HPP
#define ELABORATO_ING_SW_WINDOW_HPP

#include "../interfaces/ISubject.hpp"

namespace mm {
    /*!
     * Classe astratta utilizzata come base per tutti gli altri controllori delle finestre.
     */

    enum WindowName {
        LOGIN = 0,
        MAIN
    };

    class Window : public ISubject {
    public:
        virtual bool init() = 0; // imposta tutti i gestori delle chiamate di tutti gli eventi che lo riguardano.
        virtual WindowName getName() const = 0; // Ritorna il nome della classe, serve per capire che controllore è i
        // nstanziato
        virtual WindowName getNextWindow() const = 0;   // Deve ritornare il nome della classe che dovrà essere come
        // controllore successivamente e questa, se il nome è uguale a
        // getName allora nulla deve essere cambiato.
    };
}


#endif //ELABORATO_ING_SW_WINDOW_HPP
