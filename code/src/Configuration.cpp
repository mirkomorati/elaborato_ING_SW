//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/Configuration.hpp"
#include <stdexcept>

mm::Configuration *mm::Configuration::instance = nullptr;
std::string mm::Configuration::config_file_name;

mm::Configuration::Configuration() noexcept(false) {
  if (Configuration::config_file_name.empty())
    throw std::invalid_argument(
        "Set the path of the configuration file first. with a call to "
            "mm::Configuration::set_db_file_name()");

  std::ifstream config_file(Configuration::config_file_name);

  if(config_file.fail())
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

  if (instance != nullptr){
    delete instance;
    instance = nullptr;
  }
}