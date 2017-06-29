/*
#include "../hdr/Configuration.hpp"
#include "../hdr/DBMaster.hpp"
#include "../hdr/Drug.hpp"

using namespace mm;

int main(int argc, char **argv){
  Configuration::set_config_file_name(
      "../tmp/config.json");

  Configuration &config = Configuration::get_instance();

  std::cout << "configuration from: " << config.get_config_file_name()
            << std::endl << "\tdb_name: "
            << config.get<std::string>("db_name") << std::endl;

  DBMaster::set_db_file_name(config.get<std::string>("db_name"));

  auto &db = DBMaster::get_instance();

  Drug to_add("ciao", 22.4f);
  to_add.ATC_classification = "testing testing testing";
  to_add.pharmaceutical_form = "water";
  to_add.contraindications.push_back("death hello");
  to_add.contraindications.push_back("test");

  db.add_to_db(to_add);

  Drug tmp("", 0.f);

  db.extract_from_db(tmp, "ciao");

  std::cout << "name: " << tmp.name << "\nprice: " << tmp.price << std::endl;
}
 */

#include <gtkmm-3.0/gtkmm.h>
#include "../hdr/MVC/view/MainWindow.hpp"
#include <iostream>

using namespace mm;

int main(int argc, char **argv) {
  auto app =
      Gtk::Application::create(argc, argv,
                               "org.gtkmm.examples.base");

  MainWindow w;
  app->run(w.getWindow());
}