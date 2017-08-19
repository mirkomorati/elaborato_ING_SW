//
// Created by Noè Murr on 19/08/2017.
//

#include "../hdr/log.hpp"

mm::Logger &mm::LoggerFactory::get_logger(string name) {

    if (loggers.find(name) == loggers.end()) {

    } else {
        return loggers.at(name);
    }
}

mm::LoggerFactory &mm::LoggerFactory::get_instance() {
    static LoggerFactory instance;
    return instance;
}

