//
// Created by Noè Murr on 03/06/2017.
//

#include "DBMaster.hpp"
#include <sstream>
#include <iostream>
#include <fmt/format.h>

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
    assert(not DBMaster::db_file_name.empty());

    if (sqlite3_open(DBMaster::db_file_name.c_str(), &db)) {
        cout << sqlite3_errmsg(db) << endl;
        throw std::runtime_error(fmt::format("Error cannot open database from file: {}", DBMaster::db_file_name));
    }
}

mm::DBMaster::~DBMaster() {
    sqlite3_close(db);
    delete instance;
}

mm::DBMaster &mm::DBMaster::get_instance() {
    if (not instance) instance = new DBMaster();

    return *instance;
}

void mm::DBMaster::add_to_db(const mm::ISerializable &obj) {
    sqlite3_stmt *stmt;
    std::stringstream ss;
    auto primary_keys = obj.get_primary_key();

    // preparing query
    ss << "select count(*) from (select * from " << obj.get_table_name()
       << " where ";

    for (size_t i = 0; i < primary_keys.size(); ++i) {
        ss << primary_keys[i] << " = " << obj.serialize()[primary_keys[i]];
        if (i + 1 < primary_keys.size()) // there is at least one other key
            ss << " and ";
        else // there is no more keys
            ss << ");";
    }

    if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if ((sqlite3_step(stmt)) == SQLITE_ROW) {
            auto serialized_map = obj.serialize();
            if (sqlite3_column_int(stmt, 0) >= 1) {
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
                ss << " where ";
                for (size_t i = 0; i < primary_keys.size(); ++i) {
                    ss << primary_keys[i] << " = " << obj.serialize()[primary_keys[i]];
                    if (i + 1 < primary_keys.size()) // there is at least one other key
                        ss << " and ";
                }

                sqlite3_finalize(stmt); // previous stmt

                if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, nullptr) == SQLITE_ERROR) {
                    throw std::runtime_error(
                            fmt::format("cannot update row with query: \"{}\"\nsqlite error: {}", ss.str(),
                                        sqlite3_errmsg(db)));
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

                if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, nullptr) == SQLITE_ERROR) {
                    throw std::runtime_error(
                            fmt::format("cannot update row with query: \"{}\"\nsqlite error: {}", ss.str(),
                                        sqlite3_errmsg(db)));
                }
            }
        } else {
            sqlite3_finalize(stmt);
            throw std::runtime_error("cannot execute stmt");
        }
    } else {
        throw std::runtime_error(fmt::format("cannot prepare stmt\nsqlite error: {}", sqlite3_errmsg(db)));
    }

    if ((sqlite3_step(stmt)) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        std::stringstream msg;
        throw std::runtime_error(
                fmt::format("cannot execute insert stmt: \"{}\"\nsqlite error: {}", ss.str(), sqlite3_errmsg(db)));
    }
    sqlite3_finalize(stmt);
}

void mm::DBMaster::extract_from_db(mm::ISerializable &obj, initializer_list<Serialized> ids) {
    // query
    std::stringstream query;
    std::map<std::string, Serialized> serialized_map;
    sqlite3_stmt *stmt;
    int col_num = 0;
    vector<Serialized> primary_keys_values(ids);
    auto primary_keys = obj.get_primary_key();
    auto length = (primary_keys_values.size() > primary_keys.size()) ? primary_keys.size() : primary_keys_values.size();

    query << "select * from " << obj.get_table_name() << " where ";

    for (size_t i = 0; i < length; ++i) {
        query << primary_keys[i] << " = " << primary_keys_values[i];
        if (i + 1 < length) // there is at least one other key
            query << " and ";
    }

    if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_ERROR) {
        throw std::runtime_error(
                fmt::format("cannot select row with query: \"{}\"\nsqlite error: {}", query.str(), sqlite3_errmsg(db)));
    }

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR) {
        sqlite3_finalize(stmt);
        throw std::runtime_error(fmt::format("cannot execute select statement: \"{}\"\nsqlite error: {}", query.str(),
                                             sqlite3_errmsg(db)));
    } else if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        std::stringstream msg;
        msg << "there are no rows that correspond to the query: " << query.str();
        throw record_not_found_error(fmt::format("there are no rows that correspond to the query: {}", query.str()));
    }

    col_num = sqlite3_column_count(stmt);

    for (int i = 0; i < col_num; ++i) {
        int type = sqlite3_column_type(stmt, i);

        switch (type) {
            case SQLITE_INTEGER:
                serialized_map[sqlite3_column_name(stmt, i)] = sqlite3_column_int(stmt, i);
                break;
            case SQLITE_TEXT:
                serialized_map[sqlite3_column_name(stmt, i)] =
                        std::string((const char *) sqlite3_column_text(stmt, i));
                break;
            case SQLITE_FLOAT:
                serialized_map[sqlite3_column_name(stmt, i)] = sqlite3_column_double(stmt, i);
                break;
            case SQLITE_NULL: {
                string t(sqlite3_column_decltype(stmt, i));
                if (t == "TEXT") {
                    serialized_map[sqlite3_column_name(stmt, i)] = "";
                } else if (t == "REAL") {
                    serialized_map[sqlite3_column_name(stmt, i)] = 0.0f;
                } else {
                    serialized_map[sqlite3_column_name(stmt, i)] = 0;
                }
                break;
            }
            default: {
                sqlite3_finalize(stmt);
                throw std::runtime_error(
                        fmt::format("data type not recognized: {}, name: {}, decltype: {}, data: {}, col: {}",
                                    type, sqlite3_column_name(stmt, i), sqlite3_column_decltype(stmt, i),
                                    sqlite3_column_int(stmt, i), i)
                );
            }
        }
    }
    sqlite3_finalize(stmt);

    obj.unserialize(serialized_map);
}

vector<map<string, mm::Serialized>>
mm::DBMaster::get_rows(string table_name, string id_name, mm::Serialized id) {
    stringstream query;
    sqlite3_stmt *stmt;
    vector<map<string, mm::Serialized>> to_return;

    query << "select * from " << table_name;
    if (not(id.get_type() == TEXT && id.get_str().empty() && id_name.empty())) {
        query << " where " << id_name << "='";
        switch (id.get_type()) {
            case INTEGER:
                query << id.get_int() << "'";
                break;
            case REAL:
                query << id.get_real() << "'";
                break;
            case TEXT:
                query << id.get_str() << "'";
                break;
        }
    }

    if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_ERROR) {
        throw std::runtime_error(fmt::format("cannot select rows with query: \"{}\"\nsqlite error{}",
                                             query.str(), sqlite3_errmsg(db)));
    }

    int col_num = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        map<string, Serialized> serialized_map;
        for (int i = 0; i < col_num; ++i) {
            int type = sqlite3_column_type(stmt, i);

            switch (type) {
                case SQLITE_INTEGER:
                    serialized_map[sqlite3_column_name(stmt, i)] = sqlite3_column_int(stmt, i);
                    break;
                case SQLITE_TEXT:
                    serialized_map[sqlite3_column_name(stmt, i)] =
                            std::string((const char *) sqlite3_column_text(stmt, i));
                    break;
                case SQLITE_FLOAT:
                    serialized_map[sqlite3_column_name(stmt, i)] = sqlite3_column_double(stmt, i);
                    break;
                case SQLITE_NULL: {
                    string t(sqlite3_column_decltype(stmt, i));
                    if (t == "TEXT") {
                        serialized_map[sqlite3_column_name(stmt, i)] = "";
                    } else if (t == "REAL") {
                        serialized_map[sqlite3_column_name(stmt, i)] = 0.0f;
                    } else {
                        serialized_map[sqlite3_column_name(stmt, i)] = 0;
                    }
                    break;
                }
                default: {
                    sqlite3_finalize(stmt);
                    throw std::runtime_error(
                            fmt::format("data type not recognized: {}, name: {}, decltype: {}, data: {}, col: {}",
                                        type, sqlite3_column_name(stmt, i), sqlite3_column_decltype(stmt, i),
                                        sqlite3_column_int(stmt, i), i)
                    );
                }
            }
        }
        to_return.push_back(serialized_map);
    }

    return to_return;
}

void mm::DBMaster::extract_from_db(mm::ISerializable &obj, const mm::Serialized &id) {
    extract_from_db(obj, {id});
}

void mm::DBMaster::remove_from_db(const mm::ISerializable &obj) {
    std::stringstream query;
    auto primary_keys_names = obj.get_primary_key();
    auto obj_map = obj.serialize();
    sqlite3_stmt *stmt;

    query << "delete from " << obj.get_table_name() << " where ";

    for (size_t i = 0; i < primary_keys_names.size(); ++i) {
        query << primary_keys_names[i] << " = " << obj_map[primary_keys_names[i]] << "";

        if (i + 1 < primary_keys_names.size()) // there is at least one other key
            query << " and ";
    }

    if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_ERROR) {
        throw std::runtime_error(fmt::format("cannot delete row with query: \"{}\"\nsqlite error{}",
                                             query.str(), sqlite3_errmsg(db)));
    }

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR) {
        sqlite3_finalize(stmt);
        throw std::runtime_error(fmt::format("cannot execute stmt: \"{}\"\nsqlite error{}",
                                             query.str(), sqlite3_errmsg(db)));
    }

    sqlite3_finalize(stmt);

}

bool mm::DBMaster::exists(string table_name, string id_name, mm::Serialized id) {
    string query;
    sqlite3_stmt *stmt;

    switch (id.get_type()) {
        case INTEGER:
            query = fmt::format("select count(1) from {} where {} = {}", table_name, id_name, to_string(id.get_int()));
            break;
        case REAL:
            query = fmt::format("select count(1) from {} where {} = {}", table_name, id_name, to_string(id.get_real()));
            break;
        case TEXT:
            query = fmt::format("select count(1) from {} where {} = {}", table_name, id_name, id.get_str());
            break;
    }

    if (sqlite3_prepare(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error(fmt::format("cannot prepare statement with query {}", query));

    auto rc = sqlite3_step(stmt);

    if (rc == SQLITE_ERROR) throw std::runtime_error(fmt::format("cannot exec query {}", query));

    return rc == SQLITE_ROW and sqlite3_column_int(stmt, 0) >= 1;

}

mm::record_not_found_error::record_not_found_error(const char *msg)
        : std::runtime_error(msg) {}

mm::record_not_found_error::record_not_found_error(const std::string &msg)
        : std::runtime_error(msg) {}

const char *mm::record_not_found_error::what() const noexcept {
    return std::runtime_error::what();
}

