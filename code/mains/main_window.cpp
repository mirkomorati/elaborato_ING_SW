#include "../hdr/MVC/view/ViewWindow.hpp"
#include <iostream>

using namespace mm;

int main(int argc, char **argv) {
  auto app =
      Gtk::Application::create(argc, argv,
                               "org.gtkmm.examples.base");

  ViewWindow w = ViewWindow("loginWindow");
  app->run(w.getViewWindow());
}