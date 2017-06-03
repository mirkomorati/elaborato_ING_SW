//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/DBMaster.hpp"

std::string mm::DBMaster::db_file_name;

const std::string &mm::DBMaster::get_db_file_name() {
  return db_file_name;
}

void mm::DBMaster::set_db_file_name(const std::string &db_file_name) {
  DBMaster::db_file_name = db_file_name;
}

mm::DBMaster::DBMaster(std::string db_file_name) {

}
