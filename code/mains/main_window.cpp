#include "../hdr/controller/MainController.hpp"
#include "../hdr/DBMaster.hpp"
#include "../hdr/Configuration.hpp"
#include <gtkmm-3.0/gtkmm.h>

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

    MainController mc;
    mc.run();

    return 0;
}