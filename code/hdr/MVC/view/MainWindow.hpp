//
// Created by Mirko Morati on 04/06/17.
//

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <gtkmm-3.0/gtkmm.h>

namespace mm {
  class MainWindow {
  public:
    MainWindow();
    virtual ~MainWindow();
    Gtk::ApplicationWindow &getWindow();

  private:
    Gtk::ApplicationWindow *window;

  protected:
    //Signal handlers

    //Child widgets
    Glib::RefPtr<Gtk::Builder> refBuilder;
  };
}

#endif //_MAINWINDOW_H