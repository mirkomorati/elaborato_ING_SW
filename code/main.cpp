//
// Created by Mirko Morati on 15/09/17.
//


#include "MedH.hpp"

int main(int argc, char **argv) {

    if (not mm::MedH::init()) return -1;

    mm::MedH my_app(argc, argv);

    return my_app.run();
}