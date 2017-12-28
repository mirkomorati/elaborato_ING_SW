//
// Created by Mirko Morati on 02/12/17.
//

#include <iostream>
#include <spdlog/spdlog.h>
#include "Widgets.hpp"
#include "RefBuilder.hpp"
#include "../utils/Date.hpp"

void mm::EntryController::entryTextChanged(const Glib::ustring &, int *) {
    if (entry == nullptr) return;
    Glib::ustring n_text = entry->get_text().uppercase();
    entry->set_text(n_text);
}

mm::EntryController::EntryController(const std::string &entryId) {
    RefBuilder::get_instance().get_widget(entryId, entry);
    this->entry->signal_insert_text().connect(sigc::mem_fun(this, &mm::EntryController::entryTextChanged));
}

mm::DateController::DateController(const std::string &dayId, const std::string &monthId, const std::string &yearId) {
    auto refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget(dayId, day);
    refBuilder.get_widget(monthId, month);
    refBuilder.get_widget(yearId, year);

    // Devo fare l'init solo la prima volta, altrimenti vado a raddoppiare/ecc gli elementi
    if (day->get_active_text() == "") init();
    reset(); // NB. quando si effettua un set da sw viene lanciato un signal changed... se si sposta
    // il reset dopo aver definito i gestori dei segnali crasha tutto.

    day->signal_changed().connect(sigc::mem_fun(this, &mm::DateController::onDateChanged));
    month->signal_changed().connect(sigc::mem_fun(this, &mm::DateController::onDateChanged));
    year->signal_changed().connect(sigc::mem_fun(this, &mm::DateController::onDateChanged));
}

void mm::DateController::reset() {
    day->set_active_text(Glib::ustring::format(util::Date::get_current_day()));
    month->set_active_text(Glib::ustring(util::Date::get_current_month() < 10 ? "0" : "").append(
            Glib::ustring::format(util::Date::get_current_month())));
    year->set_active_text(Glib::ustring::format(util::Date::get_current_year()));
}

void mm::DateController::onDateChanged() {
    auto date = getDate();

    if (!date.is_valid()) {
        if ((date.day >= 29 && date.day <= 31) && date.month == 2) {
            day->set_active_text(Glib::ustring("28"));
            month->set_active_text(Glib::ustring("02"));
            year->set_active_text(Glib::ustring::format(date.year));
        } else {
            day->set_active_text(Glib::ustring("30"));
            month->set_active_text(Glib::ustring::format(date.month));
            year->set_active_text(Glib::ustring::format(date.year));
        }
    }
}

mm::util::Date mm::DateController::getDate() {
    int tmpDay, tmpMonth, tmpYear;

    try {
        tmpDay = std::stoi(day->get_active_text().c_str());
        tmpMonth = std::stoi(month->get_active_text().c_str());
        tmpYear = std::stoi(year->get_active_text().c_str());
    } catch (...) {
        throw std::logic_error("wrong data from a combo box?! that's no good!");
    }

    return {tmpDay, tmpMonth, tmpYear};
}

void mm::DateController::init() {
    for (int i = 1; i <= 31; i++)
        day->append(Glib::ustring::format(i));
    for (int i = 1; i <= 12; i++)
        month->append(Glib::ustring((i < 10 ? "0" : "")).append(Glib::ustring::format(i)));
    for (int i = util::Date::get_current_year(); i >= 1920; i--)
        year->append(Glib::ustring::format(i));
}
