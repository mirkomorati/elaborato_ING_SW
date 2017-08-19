//
// Created by Noè Murr on 06/06/2017.
//

#include "../hdr/Configuration.hpp"
#include "../hdr/log.hpp"

using namespace mm;
using namespace std;

int main(int argc, char **argv) {
    Configuration::set_config_file_name(
            "../tmp/config.json");

    Configuration &config = Configuration::get_instance();

    cout << "configuration from: " << config.get_config_file_name()
         << endl << "\tdb_name: "
         << config.get<std::string>("db_name") << endl;

    LoggerFactory::init(config);

    Logger &log = LoggerFactory::get_instance().get_logger("test");

    log << "proviamo " << 1 << " " << 2.0f << " " << 3.2 << false << endl;

    return 0;
}