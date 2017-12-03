//
// Created by Mirko Morati on 02/12/17.
//

#include <iostream>
#include "Widgets.hpp"
#include "RefBuilder.hpp"

void mm::EntryController::entryTextChanged(const Glib::ustring &text, int *pos) {
    if (entry == nullptr) return;
    Glib::ustring n_text = entry->get_text().uppercase();
    entry->set_text(n_text);
}

mm::EntryController::EntryController(const std::string &entryId) {
    RefBuilder::get_instance().get_widget(entryId, entry);
    this->entry->signal_insert_text().connect(sigc::mem_fun(this, &mm::EntryController::entryTextChanged));
}

