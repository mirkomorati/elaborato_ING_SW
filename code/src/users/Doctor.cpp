/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../../hdr/users/Doctor.hpp"

/**
 * Doctor implementation
 */
map<string, mm::Serialized> mm::Doctor::serialize() const {
  return nullptr;
}

void mm::Doctor::unserialize(map<string, mm::Serialized> map1) {

}

string mm::Doctor::get_table_name() const {
  return nullptr;
}

string mm::Doctor::get_primary_key() const {
  return nullptr;
}

vector<mm::Prescription>
mm::Doctor::get_prescriptions(mm::Patient patient, mm::Date start,
                              mm::Date end) {
  return vector<mm::Prescription, allocator<mm::Prescription>>();
}

vector<mm::Prescription, allocator<mm::Prescription>>
mm::Doctor::get_prescriptions(mm::Drug drug) {
  return vector<mm::Prescription, allocator<mm::Prescription>>();
}

vector<mm::Drug, allocator<mm::Drug>>
mm::Doctor::get_drugs(mm::Date start, mm::Date end) {
  return vector<mm::Drug, allocator<mm::Drug>>();
}

vector<mm::Patient, allocator<mm::Patient>> mm::Doctor::get_patients() {
  return vector<mm::Patient, allocator<mm::Patient>>();
}

vector<mm::Patient, allocator<mm::Patient>>
mm::Doctor::get_patients(mm::Drug drug) {
  return vector<mm::Patient, allocator<mm::Patient>>();
}
