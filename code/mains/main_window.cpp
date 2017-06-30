#include "../hdr/MVC/view/MainWindow.hpp"
#include "../hdr/MVC/controller/MainController.hpp"
#include "../hdr/MVC/model/MainModel.hpp"
#include "../hdr/DBMaster.hpp"
#include "../hdr/Configuration.hpp"
#include <iostream>

using namespace mm;
using namespace std;

int main(int argc, char **argv) {
  Configuration::set_config_file_name(
      "../tmp/config.json");

  Configuration &config = Configuration::get_instance();

  cout << "configuration from: " << config.get_config_file_name()
       << endl << "\tdb_name: "
       << config.get<std::string>("db_name") << endl;

  DBMaster::set_db_file_name(config.get<string>("db_name"));

  auto &db = DBMaster::get_instance();

  auto app =
      Gtk::Application::create(argc, argv,
                               "org.gtkmm.examples.base");

  MainController mc;
  MainWindow mw = MainWindow("mainWindow", &mc);
  MainModel mm = MainModel(&mc);
  mc.setModel(&mm);
  mc.setWindow(&mw);
  app->run(mw.getMainWindow());
}