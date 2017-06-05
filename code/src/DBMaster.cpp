//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/DBMaster.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

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

void mm::DBMaster::add_to_db(const mm::ISerializable &obj) {
  sqlite3_stmt *stmt;
  std::stringstream ss;

  // preparing query
  ss << "select count(*) from (select * from " << obj.get_table_name()
     << " where " << obj.get_primary_key() << "="
     << obj.serialize()[obj.get_primary_key()] << ");";

  if (sqlite3_prepare(db,ss.str().c_str(), -1, &stmt, 0) == SQLITE_OK){
    if ((sqlite3_step(stmt)) == SQLITE_ROW) {
      auto serialized_map = obj.serialize();
      if(sqlite3_column_int(stmt, 0) >= 1){
        // esiste già la entry opera un update.
        ss.str(std::string());
        ss << "update " << obj.get_table_name() << " set ";
        for (auto it = serialized_map.begin(); it != serialized_map.end();) {
          ss << it->first << "=" << it->second << "";
          if (++it != serialized_map.end())
            ss << ", ";
          else
            ss << " ";
        }
        ss << " where " << obj.get_primary_key() << "="
           << obj.serialize()[obj.get_primary_key()] << ";";

        sqlite3_finalize(stmt); // previous stmt

        if (sqlite3_prepare(db,ss.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR){
          std::stringstream msg;
          msg << "cannot update row with query: \"" << ss.str() << "\""
              << std::endl
              << "sqlite error: " << sqlite3_errmsg(db);
          throw std::runtime_error(msg.str());
        }
      } else {
        // la entry non esiste opera un insert.
        ss.str(std::string());
        ss << "insert into " << obj.get_table_name() << " (";
        for (auto it = serialized_map.begin(); it != serialized_map.end();) {
          ss << it->first;
          if (++it != serialized_map.end())
            ss << ", ";
          else
            ss << ") ";
        }
        ss << "values (";
        for (auto it = serialized_map.begin(); it != serialized_map.end();) {
          ss << it->second;
          if (++it != serialized_map.end())
            ss << ", ";
          else
            ss << ");";
        }

        sqlite3_finalize(stmt); // previous stmt

        if (sqlite3_prepare(db,ss.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR){
          std::stringstream msg;
          msg << "cannot insert row with query: \"" << ss.str() << "\""
              << std::endl
              << "sqlite error: " << sqlite3_errmsg(db);
          throw std::runtime_error(msg.str());
        }
      }
    } else {
      sqlite3_finalize(stmt);
      throw std::runtime_error("cannot execute stmt");
    }
  } else {
    std::stringstream msg;
    msg << "cannot prepare stmt"
        << std::endl
        << "sqlite error: " << sqlite3_errmsg(db);
    throw std::runtime_error(msg.str());
  }

  if ((sqlite3_step(stmt)) != SQLITE_DONE){
    sqlite3_finalize(stmt);
    std::stringstream msg;
    msg << "cannot execute insert stmt: \"" << ss.str() << "\""
        << std::endl
        << "sqlite error: " << sqlite3_errmsg(db);
    throw std::runtime_error(msg.str());
  }
  sqlite3_finalize(stmt);
}

void mm::DBMaster::extract_from_db(mm::ISerializable &obj, const Serialized &id) {
  // query
  std::stringstream query;
  std::map<std::string, Serialized> serialized_map;
  sqlite3_stmt *stmt;
  int col_num = 0;

  query << "select * from " << obj.get_table_name()
        << " where " << obj.get_table_name() << " = " << id;

  if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
    std::stringstream msg;
    msg << "cannot select rows with query: \"" << query.str() << "\""
        << std::endl
        << "sqlite error: " << sqlite3_errmsg(db);
    throw std::runtime_error(msg.str());
  }

  if ((sqlite3_step(stmt)) == SQLITE_ERROR){
    sqlite3_finalize(stmt);
    std::stringstream msg;
    msg << "cannot execute insert stmt: \"" << query.str() << "\""
        << std::endl
        << "sqlite error: " << sqlite3_errmsg(db);
    throw std::runtime_error(msg.str());
  }

  col_num = sqlite3_column_count(stmt);

  for (int i = 0; i < col_num; ++i) {
    SerializedUnion tmp;
    int type = sqlite3_column_type(stmt, i);

    switch (type) {
      case SQLITE_INTEGER:
        tmp.integer = sqlite3_column_int(stmt, i);
        serialized_map[sqlite3_column_name(stmt, i)] = Serialized(mm::INTEGER, tmp);
        break;
      case SQLITE_TEXT:
        tmp.text = (const char *) sqlite3_column_text(stmt, i);
        serialized_map[sqlite3_column_name(stmt, i)] = Serialized(mm::TEXT, tmp);
        break;
      case SQLITE_FLOAT:
        tmp.real = sqlite3_column_double(stmt, i);
        serialized_map[sqlite3_column_name(stmt, i)] = Serialized(mm::REAL, tmp);
        break;
      default:{
        sqlite3_finalize(stmt);
        throw std::runtime_error("data type not recognized");
      }
    }
  }
  sqlite3_finalize(stmt);

  obj.unserialize(serialized_map);
}
