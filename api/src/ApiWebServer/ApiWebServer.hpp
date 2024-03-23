#pragma once
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Environment.h>

#include <iostream>
#include <memory>

#include "../Database/Database.hpp"

using namespace Poco::Util;
using Poco::Net::HTTPServerResponse;
using Poco::Environment;

class ApiWebServer : public ServerApplication
{
    private:
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
        ): 
            _database(database), 
            ServerApplication() {};
        std::shared_ptr<Database> getDB();
        static void setupStandartHeaders(HTTPServerResponse& response);
};