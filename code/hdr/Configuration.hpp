//
// Created by Noè Murr on 03/06/2017.
//

#ifndef ELABORATO_ING_SW_CONFIGURATION_HPP
#define ELABORATO_ING_SW_CONFIGURATION_HPP

#include <string>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace mm {
  class key_not_found_error : std::runtime_error{
  public:
    key_not_found_error(const std::string &what);
    key_not_found_error(const char *what);

  private:
    const char *what() const noexcept override;

  };

  class Configuration {
  private:
    static std::string config_file_name;
    static Configuration *instance;

    json config;

  private:
    Configuration() noexcept(false);
  public:
    // disallow default constructor and assign operator
    Configuration(const Configuration &old) = delete;
    const Configuration &operator=(const Configuration &old) = delete;

    static Configuration &get_instance() noexcept(false);

    static const std::string &get_config_file_name();

    static void set_config_file_name(const std::string &config_file_name);

    template <typename T> T get(std::string key) const noexcept(false){
      if (config.find(key) == config.end()) {
        std::stringstream ss;
        ss << "cannot find key: " << key;
        throw key_not_found_error(ss.str());
      }
      return config[key].get<T>();
    }

  };
}


#endif //ELABORATO_ING_SW_CONFIGURATION_HPP