#include <iostream>
#include "../include/sqlite3_database.h"


int main() {
    // Example

    sqlite3_database db("test.db");

    db.insert("CREATE TABLE IF NOT EXISTS people (id integer, name text)");
    db.insert("INSERT INTO people (id, name) VALUES (0, 'Peter')");
    db.insert("INSERT INTO people (id, name) VALUES (1, 'Markus')");

    auto res = db.select("SELECT * FROM people");

    for (const auto& row : res) {
        for (const auto& i : row) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
