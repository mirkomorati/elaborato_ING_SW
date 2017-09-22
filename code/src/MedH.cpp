//
// Created by Noè Murr on 22/09/2017.
//

#include "../hdr/MedH.hpp"
#include "../hdr/Configuration.hpp"
#include "../hdr/DBMaster.hpp"

mm::MedH::MedH() : main_view(main_controller), login_view(main_controller), app_view(app_controller) {}

int mm::MedH::run(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "it.mm.org");

    app->run(main_view.get_app_window());

    return 0;
}

void mm::MedH::init() {
    Glib::init();

    Configuration::set_config_file_name("../../../../tmp/config.json");

    Configuration &config = Configuration::get_instance();

    cout << "configuration from: " << config.get_config_file_name()
         << endl << "\tdb_name: "
         << config.get<std::string>("db_name") << endl
         << "glade file : " << config.get<std::string>("glade_file");

    DBMaster::set_db_file_name(config.get<string>("db_name"));
}
