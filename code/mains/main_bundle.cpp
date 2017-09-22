//
// Created by Mirko Morati on 15/09/17.
//

#include "../hdr/controller/Main.hpp"
#include "../hdr/DBMaster.hpp"
#include "../hdr/Configuration.hpp"

using namespace mm;
using namespace std;

int main(int argc, char **argv) {
    Glib::init();

    Configuration::set_config_file_name("../../../../tmp/config.json");

    Configuration &config = Configuration::get_instance();

    cout << "configuration from: " << config.get_config_file_name()
         << endl << "\tdb_name: "
         << config.get<std::string>("db_name") << endl;

    DBMaster::set_db_file_name(config.get<string>("db_name"));

    auto app = Gtk::Application::create(argc, argv, "it.mm.org");

    controller::Main mc;
    mc.setup();

    app->run(mc.get_main_window());

    return 0;
}