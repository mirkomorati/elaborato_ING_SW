//
// Created by Mirko Morati on 04/07/17.
//

#include <iostream>
#include "RefBuilder.hpp"
#include "../Configuration.hpp"

#if !defined(GLADE_FILE_NAME) || !defined(GLADE_CSS_FILE)
#error "Glade files path not defined! Use -DGLADE_FILE_NAME=file_path and -DGLADE_CSS_FILE=file_path to define them!"
#endif

mm::RefBuilder *mm::RefBuilder::instance;

mm::RefBuilder &mm::RefBuilder::get_instance() {
    if (not instance) instance = new RefBuilder();

    return *instance;
}

mm::RefBuilder::RefBuilder() {
    try {
        refBuilder = Gtk::Builder::create_from_file(GLADE_FILE_NAME);

        auto css_provider = Gtk::CssProvider::create();
        css_provider->load_from_path(GLADE_CSS_FILE);
        Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css_provider, 800);
        // 800 = Gtk::STYLE_PROVIDER_PRIORITY_USER che non trovo
    }
    catch (const Glib::ConvertError &ex) {
        std::cerr << "ConvertError: " << ex.what() << std::endl;
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }
    catch (Gtk::CssProviderError &ex) {
        std::cerr << "CssProviderError: " << ex.what() << std::endl;
    }
}