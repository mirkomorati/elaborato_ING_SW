//
// Created by Noè Murr on 03/06/2017.
//

#include "Configuration.hpp"

mm::Configuration *mm::Configuration::instance = nullptr;
std::string mm::Configuration::config_file_name;

mm::Configuration::Configuration() noexcept(false) {
    assert(not config_file_name.empty());

    std::ifstream config_file(Configuration::config_file_name);

    if (config_file.fail())
        throw std::runtime_error("Cannot open the configuration file");

    // reading json
    config_file >> config;
}

mm::Configuration &mm::Configuration::get_instance() noexcept(false) {
    if (instance == nullptr) instance = new Configuration();

    return *instance;
}

const std::string &mm::Configuration::get_config_file_name() {
    return Configuration::config_file_name;
}

void
mm::Configuration::set_config_file_name(const std::string &config_file_name) {
    Configuration::config_file_name = config_file_name;

    delete instance;
    instance = nullptr;
}

mm::Configuration::~Configuration() {
    delete instance;
}

mm::key_not_found_error::key_not_found_error(const std::string &str)
        : runtime_error(str) {}

const char *mm::key_not_found_error::what() const noexcept {
    return std::runtime_error::what();
}

mm::key_not_found_error::key_not_found_error(const char *what)
        : runtime_error(what) {}
