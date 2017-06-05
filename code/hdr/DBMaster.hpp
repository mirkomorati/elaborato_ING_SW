//
// Created by Noè Murr on 03/06/2017.
//

#ifndef ELABORATO_ING_SW_DBMASTER_HPP
#define ELABORATO_ING_SW_DBMASTER_HPP

#include <sqlite3.h>
#include <string>
#include "interfaces/ISerializable.hpp"

namespace mm {
  class DBMaster {
  private:
    sqlite3 *db;
    static std::string db_file_name;
    static DBMaster *instance;
  private:
    DBMaster() noexcept(false);
  public:
    // disallow default constructor and assign operator
    DBMaster(const DBMaster &old) = delete;
    const DBMaster &operator=(const DBMaster &old) = delete;

    static const std::string &get_db_file_name();

    static void set_db_file_name(const std::string &db_file_name);

    static DBMaster &get_instance() noexcept(false);

    void add_to_db(const ISerializable &obj);

    void extract_from_db(ISerializable &obj, const Serialized &id);

    ~DBMaster();

  };
}

#endif //ELABORATO_ING_SW_DBMASTER_HPP
