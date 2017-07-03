//
// Created by Mirko Morati on 04/06/17.
//

#include "../../../../code/hdr/MVC/view/MainView.hpp"
#include <iostream>

mm::MainView::MainView(std::string window_id, MainController *controller)
    : controller(controller) {
    try {
        refBuilder = Gtk::Builder::create_from_file(
            "../glade/mainWindow.glade");
    }
    catch (const Glib::ConvertError &ex) {
        std::cerr << "ConvertError: " << ex.what() << std::endl;
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    refBuilder->get_widget(window_id, window);
    refBuilder->get_widget("loginButton", login_button);

    login_view = new LoginView(this, refBuilder, login_mutex);

    //////////////////
    // SKIPPO IL LOGIN
    //////////////////
    //login_update(222);
}

mm::MainView::~MainView() {
    if (window) delete window;
    if (login_view) delete login_view;
    if (patient_tree_view) delete patient_tree_view;
}


Gtk::ApplicationWindow &mm::MainView::getMainWindow() {
    return *window;
}

void mm::MainView::onLoginButtonClicked() {
    std::lock_guard<std::mutex> lock(mutex);
    Gtk::Entry *login_name, *login_password;
    refBuilder->get_widget("loginName", login_name);
    refBuilder->get_widget("loginPassword", login_password);

    controller->login(login_name->get_text(),
                      login_password->get_text());
}

void mm::MainView::login_update(int doctor_id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (doctor_id != -1) {
        std::lock_guard<std::mutex> login_lock(login_mutex);
        std::cout << "Login eseguito con successo" << std::endl;
        std::cout << "Doctor_id: " << doctor_id << std::endl;
        delete login_view;
        login_view = nullptr;
        patient_view(doctor_id);
    } else {
        std::cout << "login fallito" << std::endl;
        login_view->loginFailed();
    }
}

void mm::MainView::patient_view(int doctor_id) {
    patient_tree_view = new PatientTreeView(this, refBuilder, doctor_id);
    auto &patient_cols = patient_tree_view->get_cols();

    Gtk::Stack *stack;
    Gtk::MenuBar *menu_bar;

    refBuilder->get_widget("mainStack", stack);
    refBuilder->get_widget("menuBar", menu_bar);


    row[patient_cols.first_name] = "Mirko";
    row[patient_cols.second_name] = "Morati";
    row[patient_cols.fiscal_code] = "QUALCOSA";

    row = *(refListStore->append()++);

    row[patient_cols.first_name] = "Noè";
    row[patient_cols.second_name] = "";
    row[patient_cols.fiscal_code] = "Madonna";

    patient_tree_view->append_column("Nome", patient_cols.first_name);
    patient_tree_view->append_column("Cognome", patient_cols.second_name);
    patient_tree_view->append_column("Cod. Fiscale", patient_cols.fiscal_code);
    patient_tree_view->set_model(refListStore);

    stack->set_visible_child("patientPaned");
    menu_bar->set_visible(true);
}

mm::MainController *mm::MainView::get_controller() {
    return controller;
}
