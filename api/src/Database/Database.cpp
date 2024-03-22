#include "Database.hpp"

#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using Poco::Data::Session;
using Poco::Data::SQLite::Connector;
using namespace Poco::Data::Keywords;

const std::vector<Database::Table> Database::getTables() {
    return std::vector<Table>{
        Table("link", {
            Column("id", "INTEGER PRIMARY KEY AUTOINCREMENT"),
            Column("redirect_url", "TEXT"),
            Column("url", "TEXT"),
            Column("create_date", "DATE"),
            Column("expire_date", "DATE")
        })
    };
};

void Database::registerConnector() {
    std::cout << "Connecting to Database" << std::endl;
    Connector::registerConnector();
}

Database::Database(const std::string& file_name): _session("SQLite", file_name) {
    std::cout << "Create tables" << std::endl;
    this->_file_name = file_name;
    this->_tables = this->getTables();
    for (auto table : this->_tables) {
        std::stringstream query;
        query << "CREATE TABLE IF NOT EXISTS " << table.name << " (" << std::endl;
        for (int i = 0; i < table.columns.size(); i++) {
            Column column = table.columns[i];
            query << column.name << " " << column.type;
            if (i + 1 != table.columns.size()) {
                query << ",";
            }
            query << std::endl;
        }
        query << ");";
        std::cout << "Table: " << table.name << std::endl;
        this->_session << query.str(), now;
    }
}