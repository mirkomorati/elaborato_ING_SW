//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include <giomm.h>
#include <iostream>
#include "../../hdr/view/MainView.hpp"

mm::MainView::MainView(mm::MainController &controller)
        : controller(controller), login_view(controller.get_login_controller()),
          patient_view(controller.get_patient_controller()) {
    try {
        refBuilder = Gtk::Builder::create_from_file(
                "../../glade/mainWindow.glade");
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

    refBuilder->get_widget("mainWindow", window);
}

Gtk::ApplicationWindow &mm::MainView::get_app_window() {
    return *window;
}

mm::LoginView &mm::MainView::get_login_view() {
    return login_view;
}

mm::PatientView &mm::MainView::get_patient_view() {
    return patient_view;
}


