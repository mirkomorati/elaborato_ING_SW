#include "../hdr/MVC/view/MainWindow.hpp"
#include "../hdr/MVC/controller/MainController.hpp"
#include <iostream>

using namespace mm;

int main(int argc, char **argv) {
  auto app =
      Gtk::Application::create(argc, argv,
                               "org.gtkmm.examples.base");

  MainController mc;
  MainWindow w = MainWindow("mainWindow", &mc);
  mc.setWindow(&w);
  app->run(w.getMainWindow());
}