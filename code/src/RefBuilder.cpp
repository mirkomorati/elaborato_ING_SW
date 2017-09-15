//
// Created by Mirko Morati on 04/07/17.
//

#include <iostream>
#include "../hdr/RefBuilder.hpp"

mm::RefBuilder *mm::RefBuilder::instance;

mm::RefBuilder &mm::RefBuilder::get_instance() {
    if (not instance) instance = new RefBuilder();

    return *instance;
}

mm::RefBuilder::RefBuilder() {
    try {
        /*
        refBuilder = Gtk::Builder::create_from_file(
            "../glade/mainWindow.glade");
            */
        refBuilder = Gtk::Builder::create_from_file(
                "../../../../glade/mainWindow.glade");
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
}