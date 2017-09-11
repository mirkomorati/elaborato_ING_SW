//
// Created by Mirko Morati on 03/08/17.
//

#include <iostream>
#include <string>
#include "../../hdr/controller/SelectDateDialog.hpp"
#include "../../hdr/RefBuilder.hpp"

void mm::controller::SelectDateDialog::ok_handler() {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Calendar *select_date_calendar;
    Gtk::RadioButton *by_month;
    Gtk::RadioButton *by_quarter;
    Gtk::RadioButton *by_semester;
    Gtk::RadioButton *by_year;
    std::string active;

    guint day, month, year;

    refBuilder.get_widget("selectDateCalendar", select_date_calendar);
    refBuilder.get_widget("byMonth", by_month);
    refBuilder.get_widget("byQuarter", by_quarter);
    refBuilder.get_widget("bySemester", by_semester);
    refBuilder.get_widget("byYear", by_year);

    if (by_month->get_active()) active = "month";
    else if (by_quarter->get_active()) active = "quarter";
    else if (by_semester->get_active()) active = "semester";
    else if (by_year->get_active()) active = "year";

    select_date_calendar->get_date(year, month, day);
    std::cout << "Selected date_by: " << day << "/" << month << "/" << year << " by " << active << std::endl;

    date_by = util::DateBy({(int) day, (int) month, (int) year}, active);

    parent->mask_by_selected_date(date_by);

    view->dispose_dialog();
}

void mm::controller::SelectDateDialog::cancel_handler() {
    view->dispose_dialog();
}

void mm::controller::SelectDateDialog::show_dialog() {
    view->show_dialog();
}

void mm::controller::SelectDateDialog::set_view() {
    view = new mm::view::SelectDateDialog();
    view->set_controller(this);
}

mm::controller::SelectDateDialog::~SelectDateDialog() {
    delete (view);
}

mm::util::DateBy mm::controller::SelectDateDialog::get_date() {
    return date_by;
}

void mm::controller::SelectDateDialog::set_parent(mm::controller::Patient *parent) {
    SelectDateDialog::parent = parent;
}
