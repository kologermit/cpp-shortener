#pragma once

#include <Poco/Data/Session.h>
#include <string>
#include <vector>

using Poco::Data::Session;

class Database {
    private:
        std::string _file_name;
        Session _session;
        struct Column;
        struct Table {
            std::string name;
            std::vector<Column> columns;
            Table(std::string name, std::vector<Column> columns): name(name), columns(columns) {};
        };
        struct Column {
            std::string name;
            std::string type;
            Column(std::string name, std::string type): name(name), type(type) {};
        };
        std::vector<Table> _tables;
        static const std::vector<Table> getTables();
    public:
        static void registerConnector();
        Database(const std::string& file_name);
};