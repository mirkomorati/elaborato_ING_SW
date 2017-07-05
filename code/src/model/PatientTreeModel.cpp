//
// Created by Noè Murr on 04/07/2017.
//

#include "../../hdr/model/PatientTreeModel.hpp"

mm::PatientTreeModel::PatientTreeModel() {
    add(first_name);
    add(last_name);
    add(fiscal_code);
    add(health_code);
    add(birth_date);
    add(birth_place);
    add(address);
    add(risk_factors);
}
