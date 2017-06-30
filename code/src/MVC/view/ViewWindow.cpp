//
// Created by Mirko Morati on 04/06/17.
//

#include "../../../hdr/MVC/view/ViewWindow.hpp"
#include <iostream>

mm::ViewWindow::ViewWindow(std::string window_id) {
  try {
    refBuilder = Gtk::Builder::create_from_file("../glade/mainWindow.glade");
  }
  catch(const Glib::ConvertError &ex) {
    std::cerr << "ConvertError: " << ex.what() << std::endl;
  }
  catch(const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
  }
  catch(const Glib::MarkupError& ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
  }
  catch(const Gtk::BuilderError& ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }

  refBuilder->get_widget(window_id, window);
}

mm::ViewWindow::~ViewWindow() {}


Gtk::ApplicationWindow &mm::ViewWindow::getViewWindow() {
  return *window;
}