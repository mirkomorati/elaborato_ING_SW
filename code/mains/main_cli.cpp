//
// Created by Noè Murr on 06/06/2017.
//

#include "../hdr/Configuration.hpp"
#include "../hdr/DBMaster.hpp"
#include "../hdr/Drug.hpp"
#include "../hdr/users/Doctor.hpp"
#include <plog/Log.h>

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

    plog::init(plog::debug, config.get<string>("log_name").c_str());

    LOGD << "test di log" << std::endl;

    auto &db = DBMaster::get_instance();

    Drug to_add("loro", 22.4f);
    to_add.ATC_classification = "testing testing testing";
    to_add.pharmaceutical_form = "water";
    to_add.contraindications.push_back("death hello");
    to_add.contraindications.push_back("test");
    to_add.active_principles.push_back({"test", "test1"});
    to_add.active_principles.push_back({"test2", "test3"});

    db.add_to_db(to_add);

    Drug tmp("", 0.f);

    db.extract_from_db(tmp, "loro");

    cout << "name:\t" << tmp.name << "\nprice: " << tmp.price << endl;
    cout << "active principles: " << endl;

    for (auto &p : tmp.active_principles) {
        cout << "\t" << p.first << " -> " << p.second << endl;
    }

    cout << "contraindications: " << endl;

    for (auto &p : tmp.contraindications) {
        cout << "\t" << p << endl;
    }

    cout << "pharmaceutical form:\t" << tmp.pharmaceutical_form << endl;

    cout << "ATC classification:\t" << tmp.ATC_classification << endl;


    auto table = db.get_table("drugs", 0, 4);

    cout << "uscita: ";
    for (auto row : table) {
        cout << row[0] << "\t";
    }
    cout << endl;

    Doctor me;

    db.extract_from_db(me, 222);

    cout << "mirko è: " << me.getFiscal_code() << endl;

}