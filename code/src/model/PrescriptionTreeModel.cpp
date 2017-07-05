//
// Created by Mirko Morati on 05/07/17.
//

#include "../../hdr/model/PrescriptionTreeModel.hpp"

mm::PrescriptionTreeModel::PrescriptionTreeModel() {
    add(patient_id);
    add(issue_date);
    add(expiry_date);
    add(drugs);
    add(prescription_id);
    add(negative_interactions);
    add(used);
    add(bill_id);
}