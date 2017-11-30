//
// Created by Noè Murr on 29/11/2017.
//

#include <gtkmm/button.h>
#include "MainWindow.hpp"
#include "../RefBuilder.hpp"
#include "AddPatientDialog.hpp"

bool mm::MainWindow::init() {
    Gtk::ToolButton *add_patient_button;
    Gtk::ToolButton *add_prescription_button;

    RefBuilder::get_instance().get_widget("addPatient", add_patient_button);
    RefBuilder::get_instance().get_widget("addPrescription", add_prescription_button);

    add_patient_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPatientClicked));
    add_prescription_button->signal_clicked().connect(sigc::mem_fun(this, &mm::MainWindow::onAddPrescriptionClicked));
}

mm::WindowName mm::MainWindow::getName() const {
    return MAIN;
}

mm::WindowName mm::MainWindow::getNextWindow() const {
    return next;
}

mm::MainWindow::MainWindow() : next(MAIN) {}

void mm::MainWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);

    // todo reload models and updates views.
}

void mm::MainWindow::onAddPrescriptionClicked() {

}

void mm::MainWindow::onAddPatientClicked() {
    std::unique_ptr<Dialog> dialog(new AddPatientDialog);
    dialog->show();
    dialogList.push_back(std::move(dialog));
}
