//
// Created by Noè Murr on 22/09/2017.
//

#include "MedH.hpp"
#include "Configuration.hpp"
#include "DBMaster.hpp"
#include "gui/RefBuilder.hpp"
#include "gui/LoginWindow.hpp"
#include "model/Authentication.hpp"
#include "gui/MainWindow.hpp"
#include <spdlog/spdlog.h>

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

#if defined(DEBUG) && !defined(CONFIG_FILE)
#error "Config file path not provvided compile using -DCONFIG_FILE=config_file_path"
#endif
#ifdef DEBUG
    Configuration::set_config_file_name(CONFIG_FILE);
#elif defined(CONFIG_FILE)
    if(argc < 2){
        console->info("No configuration file provvided, using the default {}", CONFIG_FILE);
        Configuration::set_config_file_name(CONFIG_FILE);
    } else {
        Configuration::set_config_file_name(argv[1]);
    }
#else
    if(argc < 2){
        console->error("No configuration file provvided! use: {} file_path", argv[0]);
        return false;
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

        console->debug("database file: {}", config.get<std::string>("db_name"));

        appID = config.get<std::string>("app_id");

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
    if (not init()) throw std::runtime_error("cannot initialize the app");
    this->app = Gtk::Application::create(argc, argv, appID);
    if (not window->init()) throw std::runtime_error("cannot initDrugComboBox the window");
    window->attach(this);
}

void mm::MedH::update() {

    if (window->getNextWindow() == window->getName()) return; // nothing to do.

    switch (window->getNextWindow()) {
        case LOGIN: {
            // session destroyed
            model::authentication::Login::get_instance().logout();
            Gtk::Stack *stack;
            RefBuilder::get_instance().get_widget("mainStack", stack);
            stack->set_visible_child("loginGrid");
            window.reset(new LoginWindow);
            break;
        }
        case MAIN: {
            Gtk::Stack *stack;
            RefBuilder::get_instance().get_widget("mainStack", stack);
            stack->set_visible_child("mainNotebook");
            window.reset(new MainWindow);
            break;
        }
        default: {
            throw std::logic_error("unknown page on MedH::update switch");
        }
    }

    window->init();
    window->attach(this);
}
