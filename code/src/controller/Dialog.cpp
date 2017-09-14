//
// Created by Mirko Morati on 14/09/17.
//

#include "../../hdr/controller/Dialog.hpp"

mm::controller::Dialog::~Dialog() {
    delete view;
}

void mm::controller::Dialog::show_dialog() {
    view->show_dialog();
}
