#include "Database.hpp"

#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Timespan.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using Poco::Data::SQLite::Connector;
using Poco::Timespan;
using Poco::Data::Statement;
using Poco::Data::RecordSet;
using namespace Poco::Data::Keywords;
using Poco::JSON::Object;
using Poco::JSON::Stringifier;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

const std::vector<Database::Table> Database::getTables() {
    return std::vector<Table>{
        Table("links", {
            Column("id", "INTEGER PRIMARY KEY AUTOINCREMENT"),
            Column("code", "TEXT"),
            Column("url", "TEXT"),
            Column("redirect_url", "TEXT"),
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

const std::string Database::Link::toJSON() const {
    Object json;
    json.set("id", this->id);
    json.set("code", this->code);
    json.set("url", this->url);
    json.set("redirect_url", this->redirect_url);
    json.set("create_date", DateTimeFormatter::format(this->create_date, DateTimeFormat::ISO8601_FORMAT));
    json.set("expire_date", DateTimeFormatter::format(this->expire_date, DateTimeFormat::ISO8601_FORMAT));
    std::stringstream res;
    Stringifier::stringify(json, res);
    return res.str();
}

Database::Link Database::createLink(const std::string& code, const std::string& url, const std::string& host) {
    Link res;
    res.code = code;
    res.url = url;
    res.redirect_url = host + "/" + code + "/";
    res.create_date = DateTime();
    res.expire_date = res.create_date + Timespan(7*24*3600, 0);
    this->_session << "INSERT INTO links (code, url, redirect_url, create_date, expire_date) VALUES(?, ?, ?, ?, ?)", 
        use(res.code), 
        use(res.url),
        use(res.redirect_url),
        use(res.create_date),
        use(res.expire_date), now;
	Statement select(this->_session);
	select << "SELECT last_insert_rowid()";
    select.execute();
    RecordSet rs(select);
    rs.moveFirst();
    res.id = rs[0].convert<int>();
    return res;
}

Database::Link Database::getLink(int& id) {
    Statement select(this->_session);
	select << "SELECT id, code, url, redirect_url, create_date, expire_date FROM links WHERE id=?", use(id), now;
    select.execute();
    RecordSet rs(select);
    Link res;
    res.id = -1;
	bool more = rs.moveFirst();
	while (more) {
        res.id = rs[0].convert<int>();
        res.code = rs[1].convert<std::string>();
        res.url = rs[2].convert<std::string>();
        res.redirect_url = rs[3].convert<std::string>();
        res.create_date = rs[4].convert<DateTime>();
        res.expire_date = rs[5].convert<DateTime>();
		more = rs.moveNext();
	}
    return res;
}

Database::Link Database::getLink(std::string code) {
    Link res;
    res.code = code;
    Statement select(this->_session);
	select << "SELECT id, code, url, redirect_url, create_date, expire_date FROM links WHERE code=?", use(res.code), now;
    select.execute();
    RecordSet rs(select);
    res.id = -1;
	bool more = rs.moveFirst();
	while (more) {
        res.id = rs[0].convert<int>();
        res.code = rs[1].convert<std::string>();
        res.url = rs[2].convert<std::string>();
        res.redirect_url = rs[3].convert<std::string>();
        res.create_date = rs[4].convert<DateTime>();
        res.expire_date = rs[5].convert<DateTime>();
		more = rs.moveNext();
	}
    return res;
}

void Database::deleteLink(Link& link) {
    this->_session << "DELETE FROM links WHERE id=?", use(link.id), now;
}