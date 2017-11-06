//
// Created by Noè Murr on 22/09/2017.
//

#include "../hdr/MedH.hpp"
#include "../hdr/Configuration.hpp"
#include "../hdr/DBMaster.hpp"
#include <spdlog/spdlog.h>

Glib::RefPtr<Gtk::Application> mm::MedH::app;

mm::MedH::MedH() : main_view(main_controller), login_view(main_controller), app_view(app_controller) {}

int mm::MedH::run() {

    return app->run(main_view.get_app_window());
}

void mm::MedH::init(int argc, char **argv) {
    Glib::init();

    Configuration::set_config_file_name("../../../../tmp/config.json");

    Configuration &config = Configuration::get_instance();

    cout << "configuration from: " << config.get_config_file_name()
         << endl << "\tdb_name: "
         << config.get<std::string>("db_name") << endl
         << "glade file : " << config.get<std::string>("glade_file");

    DBMaster::set_db_file_name(config.get<string>("db_name"));

    auto console = spdlog::stdout_color_mt("out");
    auto error = spdlog::stderr_color_mt("err");

    app = Gtk::Application::create(argc, argv, "it.mm.org");
}
