//
// Created by Noè Murr on 19/09/2017.
//

#include "IObserver.hpp"
#include "ISubject.hpp"

void mm::ISubject::attach(mm::IObserver *obj) noexcept {
    observer_set.insert(obj);
}

void mm::ISubject::detach(mm::IObserver *obj) noexcept(false) {
    if (observer_set.erase(obj) == 0) throw observer_not_found_error("cannot find observer obj");
}

void mm::ISubject::notify() const {
    // a copy of the set is necessary cause if the update function destroyes the "this"
    // object we fall in an undefined behaviuor
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
