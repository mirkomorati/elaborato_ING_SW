//
// Created by Mirko Morati on 15/09/17.
//


#include "../hdr/MedH.hpp"

int main(int argc, char **argv) {

    if (not mm::MedH::init(argc, argv)) return -1;

    mm::MedH my_app;

    return my_app.run();
}