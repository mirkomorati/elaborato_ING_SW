//
// Created by Noè Murr on 03/06/2017.
//

#ifndef ELABORATO_ING_SW_DBMASTER_HPP
#define ELABORATO_ING_SW_DBMASTER_HPP

#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include "interfaces/ISerializable.hpp"

namespace mm {

  /**
   * @brief Singleton che rappresenta il database, contiene tutte le funzioni
   *        necessarie per scrivere un oggetto di tipo derivato da ISerializable
   *        e per leggerlo. Nasconde le chiamate alle API C di sqlite3.
   */
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

  class record_not_found_error : std::runtime_error {
  public:
    record_not_found_error(const std::string &msg);

    record_not_found_error(const char *msg);

  private:
    const char *what() const noexcept override;

  };
}

#endif //ELABORATO_ING_SW_DBMASTER_HPP
