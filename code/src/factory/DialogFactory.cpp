//
// Created by Mirko Morati on 19/09/17.
//

#include "../../hdr/factory/DialogFactory.hpp"
#include "../../hdr/controller/AddPatientDialog.hpp"

mm::factory::DialogFactory::~DialogFactory() {
    factory_map.clear();
}

mm::factory::DialogFactory::DialogFactory() {
    register_dialog("AddPatientDialog", &controller::AddPatientDialog::create);
    register_dialog("AddPrescriptionDialog", &controller::AddPrescriptionDialog::create);
    register_dialog("SelectDateByDialog", &controller::SelectDateByDialog::create);
    register_dialog("SelectDateDialog", &controller::SelectDateDialog::create);
}

mm::factory::DialogFactory *mm::factory::DialogFactory::get_instance() {
    static DialogFactory instance;
    return &instance;
}

void mm::factory::DialogFactory::register_dialog(const std::string &dialog_name,
                                                 mm::factory::DialogFactory::create_dialog_function create) {
    factory_map[dialog_name] = create;
}

mm::controller::Dialog *mm::factory::DialogFactory::create_dialog(const std::string &dialog_name) {
    std::map::iterator it = factory_map.find(dialog_name);
    if (it != factory_map.end()) return it->second();
    return NULL;
}
