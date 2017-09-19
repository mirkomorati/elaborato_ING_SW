//
// Created by Mirko Morati on 14/09/17.
//

#include <gtkmm/calendar.h>
#include "../../hdr/controller/SelectDateDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::controller::SelectDateDialog::ok_handler() {
    Gtk::Calendar *select_date_calendar;
    RefBuilder::get_instance().get_widget("selectDateCalendar", select_date_calendar);

    guint day, month, year;

    select_date_calendar->get_date(year, month, day);
    std::cout << "Selected date: " << day << "/" << month << "/" << year << std::endl;

    date = mm::util::Date((int) day, (int) month, (int) year);

    parent->select_birth_date_get_date(date);

    view->dispose_dialog();
}

void mm::controller::SelectDateDialog::set_view() {
    view = new mm::view::SelectDateDialog();
    view->set_ok_handler(this, &controller::Dialog::ok_handler);
    view->set_cancel_handler(this, &controller::Dialog::cancel_handler);
}

void mm::controller::SelectDateDialog::cancel_handler() {
    view->dispose_dialog();
}

mm::util::Date mm::controller::SelectDateDialog::get_date() {
    return date;
}

void mm::controller::SelectDateDialog::set_parent(mm::controller::AddPatientDialog *parent) {
    this->parent = parent;
}

mm::controller::SelectDateDialog::~SelectDateDialog() {
    delete view;
    delete parent;
}

void mm::controller::SelectDateDialog::free() {
    std::cout << "Freed SelectDateDialog Controller: " << this << std::endl;
    delete this;
}

mm::controller::Dialog *mm::controller::SelectDateDialog::create() {
    return new SelectDateDialog();
}

mm::controller::SelectDateDialog::SelectDateDialog() {
    this->set_view();
}

void mm::controller::SelectDateDialog::show_dialog() {
    view->show_dialog();
}
