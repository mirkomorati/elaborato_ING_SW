//
// Created by Mirko Morati on 15/09/17.
//


#include "../hdr/MedH.hpp"

int main(int argc, char **argv) {

    mm::MedH::init();

    mm::MedH my_app;

    return my_app.run(argc, argv);
}