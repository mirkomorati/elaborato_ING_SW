//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/DBMaster.hpp"
#include <sstream>
#include <iostream>

std::string mm::DBMaster::db_file_name;
mm::DBMaster *mm::DBMaster::instance = nullptr;

const std::string &mm::DBMaster::get_db_file_name() {
  return db_file_name;
}

void mm::DBMaster::set_db_file_name(const std::string &db_file_name) {
  DBMaster::db_file_name = db_file_name;

  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

mm::DBMaster::DBMaster() noexcept(false) {
  if (DBMaster::db_file_name.empty()){
    throw std::invalid_argument("Set the database file before call "
          "get_instance with static call to DBMaster::set_db_file_name");
  }

  if (sqlite3_open(DBMaster::db_file_name.c_str(), &db)){
    std::stringstream ss;
    ss << "Error cannot open database from file: " << DBMaster::db_file_name;
    throw std::runtime_error(ss.str());
  }
}

mm::DBMaster::~DBMaster() {
  sqlite3_close(db);
}

mm::DBMaster &mm::DBMaster::get_instance() {
  if(instance == nullptr) instance = new DBMaster();

  return *instance;
}
