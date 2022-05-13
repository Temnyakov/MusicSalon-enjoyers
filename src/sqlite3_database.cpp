#include "../include/sqlite3_database.h"

sqlite3_database::sqlite3_database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &m_db)) {
        throw std::runtime_error("Error: can't open this sqlite3 database");
    }
}

sqlite3_database::query_result sqlite3_database::select(const std::string& sql) const {
    char* error_msg = nullptr;
    query_result result;

    if (sqlite3_exec(m_db, sql.c_str(), m_default_callback, (void*)&result, &error_msg)) {
        throw std::runtime_error("Error: " + std::string(error_msg));
    }

    return result;
}

void sqlite3_database::insert(const std::string& sql) const {
    char* error_msg = nullptr;

    if (sqlite3_exec(m_db, sql.c_str(), nullptr, nullptr, &error_msg)) {
        if (error_msg) {
            throw std::runtime_error("Error: " + std::string(error_msg));
        }
        throw std::runtime_error("Error: unknown error occurred in sqlite3_database::insert");
    }
}

void sqlite3_database::param_insert(const std::string& sql, const std::vector<std::string>& values) const {
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(m_db, sql.c_str(), sql.size(), &stmt, nullptr);

    for (int i = 0; i < values.size(); ++i) {
        sqlite3_bind_text(stmt, i + 1, values[i].c_str(), values[i].size(), nullptr);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Error: insertion was failed");
    }

    sqlite3_finalize(stmt) ;
}

void sqlite3_database::del(const std::string& sql) const {
    insert(sql);
}

int sqlite3_database::m_default_callback(void* data, int argc, char** argv, char** col_name) {
    auto& result = *static_cast<query_result*>(data);
    result.push_back(std::vector<std::string>(argc));

    for (int i = 0; i < argc; ++i) {
        result.back()[i] = argv[i] ? argv[i] : "NULL";
    }

    return 0;
}

sqlite3_database::~sqlite3_database() {
    sqlite3_close(m_db);
}
