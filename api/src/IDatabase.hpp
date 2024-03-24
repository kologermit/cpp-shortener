#pragma once
#include <Poco/DateTime.h>
using Poco::DateTime;

class IDatabase {
public:
    struct Link {
        int id;
        std::string code;
        std::string url;
        std::string redirect_url;
        DateTime create_date;
        DateTime expire_date;
    };
    virtual Link createLink(const std::string& code, const std::string& url, const std::string& host) = 0;
    virtual Link getLink(int& id) = 0;
    virtual Link getLink(std::string code) = 0;
    virtual void deleteLink(Link& link) = 0;
};