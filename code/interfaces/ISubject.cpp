//
// Created by Noè Murr on 19/09/2017.
//

#include <Carbon/Carbon.h>
#include "IObserver.hpp"
#include "ISubject.hpp"

void mm::ISubject::attach(mm::IObserver *obj) noexcept {
    observer_set.insert(obj);
}

void mm::ISubject::detach(mm::IObserver *obj) noexcept(false) {
    if (observer_set.erase(obj) == 0) throw observer_not_found_error("cannot find objserver obj");
}

void mm::ISubject::notify() const {
    // a copy of the set is necessary couse if the update function destroyes the
    // object this object we fall in an undefined behaviuor
    std::set<IObserver *> observer_copy_set = observer_set;
    for (auto obs : observer_copy_set) {
        obs->update();
    }
}

mm::ISubject::~ISubject() {
    observer_set.clear();
}

mm::observer_not_found_error::observer_not_found_error(const std::string &error) : runtime_error(error) {}

mm::observer_not_found_error::observer_not_found_error(const char *error) : runtime_error(error) {}

mm::observer_not_found_error::observer_not_found_error(const std::runtime_error &error) : runtime_error(error) {}