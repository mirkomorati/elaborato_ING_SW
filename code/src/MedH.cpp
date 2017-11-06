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

bool mm::MedH::init(int argc, char **argv) {
    Glib::init();

    auto console = spdlog::stdout_color_mt("out");
    auto error = spdlog::stderr_color_mt("err");
    error->set_level(spdlog::level::trace); // print all messages.

    Configuration::set_config_file_name("../../../../tmp/config.json");

    // configurations settings
    try {
        Configuration &config = Configuration::get_instance();

        console->info("configurations loaded from {}", config.get_config_file_name());

        try {
            if (config.get<bool>("debug")) {
                console->set_level(spdlog::level::debug);
            }
        } catch (key_not_found_error &e) {
            error->info("cannot get the debug flag in configuration... default mode applied: No debug");
        }

        console->debug("glade file: {}", config.get<std::string>("glade_file"));
        console->debug("database file: {}", config.get<std::string>("db_name"));

        DBMaster::set_db_file_name(config.get<string>("db_name"));

    } catch (invalid_argument &e) {
        error->critical(e.what());
        return false;
    } catch (runtime_error &e) {
        error->critical(e.what());
        return false;
    }

    app = Gtk::Application::create(argc, argv, "it.mm.org");
    return true;
}
