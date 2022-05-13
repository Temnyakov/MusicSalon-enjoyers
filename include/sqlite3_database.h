#ifndef SQLITE3_DATABASE_H
#define SQLITE3_DATABASE_H

#include <vector>
#include <stdexcept>
#include "sqlite3.h"

class sqlite3_database {
private:
    using query_result = std::vector<std::vector<std::string>>;

    sqlite3* m_db = nullptr;

    static int m_default_callback(void* data, int argc, char** argv, char** col_name);

public:
    explicit sqlite3_database(const std::string& db_name);

    query_result select(const std::string& sql) const;
    void insert(const std::string& sql) const;
    void param_insert(const std::string& sql, const std::vector<std::string>& values) const;
    void del(const std::string& sql) const;

    ~sqlite3_database();
};


#endif //SQLITE3_DATABASE_H
