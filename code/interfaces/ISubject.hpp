//
// Created by Noè Murr on 19/09/2017.
//

#ifndef ELABORATO_ING_SW_ISUBJECT_HPP
#define ELABORATO_ING_SW_ISUBJECT_HPP

#include <set>
#include "IObserver.hpp"

namespace mm {

    class observer_not_found_error : public std::runtime_error {
    public:

        observer_not_found_error(const std::string &error);

        observer_not_found_error(const char *error);

        observer_not_found_error(const std::runtime_error &error);

    };

    class ISubject {
        std::set<IObserver *> observer_set;

    public:
        void attach(IObserver *obj) noexcept;

        void detach(IObserver *obj) noexcept(false);

        void notify() const;

        virtual ~ISubject();

    };
}

#endif //ELABORATO_ING_SW_ISUBJECT_HPP
