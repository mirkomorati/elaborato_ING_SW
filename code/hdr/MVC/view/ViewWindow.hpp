//
// Created by Mirko Morati on 04/06/17.
//

#ifndef _VIEWWINDOW_H
#define _VIEWWINDOW_H

#include <gtkmm-3.0/gtkmm.h>

namespace mm {
  class ViewWindow {
  public:
    ViewWindow(std::string window_id);

    virtual ~ViewWindow();

    Gtk::ApplicationWindow &getViewWindow();

  private:
    Gtk::ApplicationWindow *window;

  protected:
    //Signal handlers

    //Child widgets
    Glib::RefPtr<Gtk::Builder> refBuilder;
  };
}

#endif //_VIEWWINDOW_H