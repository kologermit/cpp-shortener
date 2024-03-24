#pragma once

#include <Poco/Data/Session.h>

#include "src/IDatabase.hpp"

#include <string>
#include <vector>

using Poco::Data::Session;

class Database: public IDatabase {
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
        Link createLink(const std::string& code, const std::string& url, const std::string& host) override;
        Link getLink(int& id) override;
        Link getLink(std::string code) override;
        void deleteLink(Link& link) override;
};