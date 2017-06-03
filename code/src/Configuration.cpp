//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/Configuration.hpp"

mm::Configuration *mm::Configuration::instance = nullptr;
std::string mm::Configuration::config_file_name;

mm::Configuration::Configuration(const std::string &configuration_file_name) {

  std::ifstream config_file(configuration_file_name);

  if(config_file.fail()) throw "error opening config file";

  // reading json
  config_file >> config;
}

mm::Configuration &mm::Configuration::get_instance() noexcept(false) {
  if (Configuration::config_file_name.empty()) throw "set the "
        "configuration file name first!";

  if (instance == nullptr) instance = new Configuration(config_file_name);

  return *instance;
}

const std::string &mm::Configuration::get_config_file_name() {
  return Configuration::config_file_name;
}

void
mm::Configuration::set_config_file_name(const std::string &config_file_name) {
  Configuration::config_file_name = config_file_name;

  if (instance != nullptr) delete instance;
}
