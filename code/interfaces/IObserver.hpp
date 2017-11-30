//
// Created by Noè Murr on 19/09/2017.
//

#ifndef ELABORATO_ING_SW_IOBSERVER_HPP
#define ELABORATO_ING_SW_IOBSERVER_HPP

#include <mutex>
#include <thread>

namespace mm {
    class IObserver {
    public:
        virtual void update() = 0;

    };

}

#endif //ELABORATO_ING_SW_IOBSERVER_HPP
