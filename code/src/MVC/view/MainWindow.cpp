//
// Created by Mirko Morati on 04/06/17.
//

#include "../../../hdr/MVC/view/MainWindow.hpp"
#include <iostream>

mm::MainWindow::MainWindow(std::string window_id, MainController *controller)
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

    /*  // NON FUNZIONA
    window->add_events(Gdk::FOCUS_CHANGE_MASK);

    window->signal_key_release_event().connect([this](GdkEventKey *e) -> bool {
        if (e->keyval == GDK_KEY_Return) {
            onLoginButtonClicked();
            return true;
        }
        return false;
    }, false);
    */

    login_button->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::onLoginButtonClicked), false);
}

mm::MainWindow::~MainWindow() {
    if (window) delete window;
    if (login_button) delete login_button;
}


Gtk::ApplicationWindow &mm::MainWindow::getMainWindow() {
    return *window;
}

void mm::MainWindow::onLoginButtonClicked() {
    std::lock_guard<std::mutex> lock(mutex);
    Gtk::Entry *login_name, *login_password;
    refBuilder->get_widget("loginName", login_name);
    refBuilder->get_widget("loginPassword", login_password);

    controller->login(login_name->get_text(),
                      login_password->get_text());
}

void mm::MainWindow::loginUpdate(int doctor_id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (doctor_id != -1) {
        std::cout << "Login eseguito con successo" << std::endl;
        std::cout << "Doctor_id: " << doctor_id << std::endl;
        Gtk::Stack *stack;
        Gtk::TreeView *drug_tree_view;
        Gtk::MenuBar *menu_bar;
        refBuilder->get_widget("mainStack", stack);
        refBuilder->get_widget("drugTreeView", drug_tree_view);
        refBuilder->get_widget("menuBar", menu_bar);
        stack->set_visible_child(*drug_tree_view);
        menu_bar->set_visible(true);
    } else {
        Gtk::Label *login_error;
        refBuilder->get_widget("loginError", login_error);
        login_error->set_visible(true);
        std::cout << "login fallito" << std::endl;
    }
}
