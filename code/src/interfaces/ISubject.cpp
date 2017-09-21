//
// Created by Noè Murr on 19/09/2017.
//

#include <Carbon/Carbon.h>
#include <thread>
#include "../../hdr/interfaces/IObserver.hpp"
#include "../../hdr/interfaces/ISubject.hpp"

void mm::ISubject::attach(mm::IObserver *obj) noexcept {
    observer_set.insert(obj);
}

void mm::ISubject::detach(mm::IObserver *obj) noexcept(false) {
    if (observer_set.erase(obj) == 0) throw observer_not_found_error("cannot find objserver obj");
}

void mm::ISubject::notify() {
    // todo asincrono
    for (auto obs : observer_set) {
        obs->update();
    }
}

mm::observer_not_found_error::observer_not_found_error(const std::string &error) : runtime_error(error) {}

mm::observer_not_found_error::observer_not_found_error(const char *error) : runtime_error(error) {}

mm::observer_not_found_error::observer_not_found_error(const std::runtime_error &error) : runtime_error(error) {}
