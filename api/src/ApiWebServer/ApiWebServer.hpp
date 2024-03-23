#pragma once
#include <Poco/Util/ServerApplication.h>
#include "../Database/Database.hpp"
#include <iostream>
#include <memory>

using namespace Poco::Util;

class ApiWebServer : public ServerApplication
{
    void initialize(Application& self)
    {
        loadConfiguration();
        ServerApplication::initialize(self);
    }
    int main(const std::vector<std::string>&);
    std::shared_ptr<Database> _database;
    public:
    ApiWebServer(
        std::shared_ptr<Database> database
    ): _database(database), ServerApplication() {};
    std::shared_ptr<Database> getDB();
};