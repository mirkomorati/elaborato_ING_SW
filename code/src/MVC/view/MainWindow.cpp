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

    //////////////////
    // SKIPPO IL LOGIN
    //////////////////
    loginUpdate(222);
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

        patientView(doctor_id);
    } else {
        Gtk::Label *login_error;
        refBuilder->get_widget("loginError", login_error);
        login_error->set_visible(true);
        std::cout << "login fallito" << std::endl;
    }
}

// è qui temporaneamente
class PatientCols : public Gtk::TreeModel::ColumnRecord {
public:
    PatientCols() {
        // This order must match the column order in the .glade file
        this->add(this->first_name);
        this->add(this->second_name);
        this->add(this->fiscal_code);
    }

    // These types must match those for the model in the .glade file
    Gtk::TreeModelColumn<Glib::ustring> first_name;
    Gtk::TreeModelColumn<Glib::ustring> second_name;
    Gtk::TreeModelColumn<Glib::ustring> fiscal_code;
};

void mm::MainWindow::patientView(int doctor_id) {
    Gtk::Stack *stack;
    Gtk::MenuBar *menu_bar;
    Gtk::TreeView *patient_tree_view;
    Gtk::CellRenderer *cell_renderer;
    //Glib::RefPtr<Gtk::ListStore> patient_list_store;

    refBuilder->get_widget("mainStack", stack);
    refBuilder->get_widget("menuBar", menu_bar);
    refBuilder->get_widget("patientTreeView", patient_tree_view);

    auto patient_list = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(
        refBuilder->get_object("patientList"));

    PatientCols patient_cols;

    //patient_list->set_property("visible", true);

    Gtk::TreeModel::iterator patient_iterator = patient_list->append();
    Gtk::TreeModel::Row patient_row = *patient_iterator;

    patient_row[patient_cols.first_name] = "Mirko";
    patient_row[patient_cols.second_name] = "Morati";
    patient_row[patient_cols.fiscal_code] = "QUALCOSA";
    patient_tree_view->set_visible(true);

    stack->set_visible_child("patientPaned");
    menu_bar->set_visible(true);
}
