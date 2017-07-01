//
// Created by Noè Murr on 03/06/2017.
//

#include "../hdr/DBMaster.hpp"
#include <sstream>
#include <iostream>
#include <Carbon/Carbon.h>

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
    if (DBMaster::db_file_name.empty()) {
        throw std::invalid_argument("Set the database file before call "
                                            "get_instance with static call to DBMaster::set_db_file_name");
    }

    if (sqlite3_open(DBMaster::db_file_name.c_str(), &db)) {
        std::stringstream ss;
        ss << "Error cannot open database from file: " << DBMaster::db_file_name;
        throw std::runtime_error(ss.str());
    }
}

mm::DBMaster::~DBMaster() {
    sqlite3_close(db);
    if (instance) delete instance;
}

mm::DBMaster &mm::DBMaster::get_instance() {
    if (not instance) instance = new DBMaster();

    return *instance;
}

void mm::DBMaster::add_to_db(const mm::ISerializable &obj) {
    sqlite3_stmt *stmt;
    std::stringstream ss;


    // preparing query
    ss << "select count(*) from (select * from " << obj.get_table_name()
       << " where " << obj.get_primary_key() << "="
       << obj.serialize()[obj.get_primary_key()] << ");";

    if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, 0) == SQLITE_OK) {
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
                ss << " where " << obj.get_primary_key() << "="
                   << obj.serialize()[obj.get_primary_key()] << ";";

                sqlite3_finalize(stmt); // previous stmt

                if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
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

                if (sqlite3_prepare(db, ss.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
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

    if ((sqlite3_step(stmt)) != SQLITE_DONE) {
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
          << " where " << obj.get_primary_key() << " = " << id;

    if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
        std::stringstream msg;
        msg << "cannot select rows with query: \"" << query.str() << "\""
            << std::endl
            << "sqlite error: " << sqlite3_errmsg(db);
        throw std::runtime_error(msg.str());
    }

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR) {
        sqlite3_finalize(stmt);
        std::stringstream msg;
        msg << "cannot execute insert stmt: \"" << query.str() << "\""
            << std::endl
            << "sqlite error: " << sqlite3_errmsg(db);
        throw std::runtime_error(msg.str());
    } else if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        std::stringstream msg;
        msg << "there are no rows that correspond to the query: " << query.str();
        throw record_not_found_error(msg.str());
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
            default: {
                std::stringstream msg;
                msg << "data type not recognized: " << type << " name: "
                    << sqlite3_column_name(stmt, i) << " decltype: "
                    << sqlite3_column_decltype(stmt, i)
                    << " data: " << sqlite3_column_int(stmt, i)
                    << " col: " << i;
                sqlite3_finalize(stmt);
                throw std::runtime_error(msg.str());
            }
        }
    }
    sqlite3_finalize(stmt);

    obj.unserialize(serialized_map);
}

vector<vector<mm::Serialized>>
mm::DBMaster::get_table(string name, unsigned int limit, unsigned int offset) {
    using namespace std;
    stringstream query;
    sqlite3_stmt *stmt;
    int col_num, row;
    int st; // return ostream sqlite_step
    vector<vector<mm::Serialized>> to_return;

    if (limit == 0) {
        query << "select * from " << name;
    } else {
        query << "select * from " << name << " limit " << limit << " offset "
              << offset;
    }

    if (sqlite3_prepare(db, query.str().c_str(), -1, &stmt, 0) == SQLITE_ERROR) {
        std::stringstream msg;
        msg << "cannot select rows with query: \"" << query.str() << "\""
            << std::endl
            << "sqlite error: " << sqlite3_errmsg(db);
        throw std::runtime_error(msg.str());
    }

    col_num = sqlite3_column_count(stmt);
    row = 0;

    st = sqlite3_step(stmt);
    while (st == SQLITE_ROW) {
        to_return.push_back(vector<mm::Serialized>());
        for (int i = 0; i < col_num; ++i) {
            int type = sqlite3_column_type(stmt, i);

            switch (type) {
                case SQLITE_INTEGER:
                    to_return[row].push_back(sqlite3_column_int(stmt, i));
                    break;
                case SQLITE_TEXT:
                    to_return[row].push_back(
                            string((const char *) sqlite3_column_text(stmt, i)));
                    break;
                case SQLITE_FLOAT:
                    to_return[row].push_back(sqlite3_column_double(stmt, i));
                    break;
                default: {
                    std::stringstream msg;
                    msg << "data type not recognized: " << type << " name: "
                        << sqlite3_column_name(stmt, i) << " decltype: "
                        << sqlite3_column_decltype(stmt, i)
                        << " data: " << sqlite3_column_int(stmt, i)
                        << " col: " << i;
                    sqlite3_finalize(stmt);
                    throw std::runtime_error(msg.str());
                }
            }
        }
        st = sqlite3_step(stmt);
        row++;
    }

    if (st == SQLITE_ERROR) {
        stringstream ss;
        ss << "error stepping on database " << sqlite3_errmsg(db);
        throw runtime_error(ss.str());
    }

    sqlite3_finalize(stmt);

    return to_return;
}

vector<vector<mm::Serialized, allocator<mm::Serialized>>, allocator<vector<mm::Serialized, allocator<mm::Serialized>>>>
mm::DBMaster::get_table(string name) {
    return get_table(name, 0, 0);
}

mm::record_not_found_error::record_not_found_error(const char *msg)
        : std::runtime_error(msg) {}

mm::record_not_found_error::record_not_found_error(const std::string &msg)
        : std::runtime_error(msg) {}

const char *mm::record_not_found_error::what() const noexcept {
    return std::runtime_error::what();
}

