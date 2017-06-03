/**
 * Created by Noè Murr on 29/05/2017.
 */

/*
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char *argv[])
{
  auto app =
      Gtk::Application::create(argc, argv,
                               "org.gtkmm.examples.base");

  Gtk::Window window;
  window.set_default_size(200, 200);

  return app->run(window);
}*/

#include "../hdr/Configuration.hpp"
#include <iostream>

using namespace mm;

int main(int argc, char **argv){
  Configuration::set_config_file_name(
      "/Users/noemurr/git/elaborato_ING_SW/tmp/config.json");

  Configuration &config = Configuration::get_instance();

  std::cout << "configuration from: " << config.get_config_file_name()
            << std::endl << "\tdb_name: "
            << config.get<std::string>("db_name") << std::endl;
}