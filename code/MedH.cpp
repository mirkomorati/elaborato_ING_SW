//
// Created by Noè Murr on 22/09/2017.
//

#include "MedH.hpp"
#include "Configuration.hpp"
#include "DBMaster.hpp"
#include "RefBuilder.hpp"
#include "gui/LoginWindow.hpp"
#include <spdlog/spdlog.h>

#define DEFAULT_CONFIG_FILE "../../../../tmp/config.json"

int mm::MedH::run() {
    Gtk::Window *mainWindow;
    RefBuilder::get_instance().get_widget("mainWindow", mainWindow);
    return app->run(*mainWindow);
}

bool mm::MedH::init() {
    Glib::init();

    auto console = spdlog::stdout_color_mt("out");
    auto error = spdlog::stderr_color_mt("err");
    error->set_level(spdlog::level::trace); // print all messages.
#ifdef DEBUG
    Configuration::set_config_file_name(DEFAULT_CONFIG_FILE);
#else
    if(argc < 2){
        console->info("No configuration file provvided, using the default {}", DEFAULT_CONFIG_FILE);
        Configuration::set_config_file_name(DEFAULT_CONFIG_FILE);
    } else {
        Configuration::set_config_file_name(argv[1]);
    }
#endif

    // configurations settings
    try {
        Configuration &config = Configuration::get_instance();

        console->info("configurations successfully loaded from {}", config.get_config_file_name());

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
    return true;
}

mm::MedH::MedH(int argc, char **argv) : window(new LoginWindow) {
    this->app = Gtk::Application::create(argc, argv, "it.mm.org");
    if (not window->init()) throw std::runtime_error("cannot init the window");
    window->attach(this);
}

void mm::MedH::update() {

    if (window->getNextWindow() == window->getName()) return; // nothing to do.

    switch (window->getNextWindow()) {
        case LOGIN:
            break; // da studiare
        case MAIN: {
            Gtk::Stack *stack;
            RefBuilder::get_instance().get_widget("mainStack", stack);
            stack->set_visible_child("patientPaned");
            window.reset(nullptr); // should be window.reset(new MainWindow);
            // window->init();
            break;
        }
    }
}
