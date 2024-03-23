#pragma once

#include <Poco/Data/Session.h>
#include <Poco/DateTime.h>
#include <string>
#include <vector>

using Poco::Data::Session;
using Poco::DateTime;

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
        struct Link {
            int id;
            std::string code;
            std::string url;
            DateTime create_date;
            DateTime expire_date;
            const std::string toJSON() const;
        };
        Link createLink(const std::string& code, const std::string& url);
};