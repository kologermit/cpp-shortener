#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../Database/Database.hpp"
#include <memory>
#include <random>

using namespace Poco::Net;

class RedirectHandler : public HTTPRequestHandler
{
    std::shared_ptr<Database> _database;
    std::string _code;
public:
    RedirectHandler(
        std::shared_ptr<Database> database,
        std::string& code
    ): 
        _database(database), 
        _code(code),
        HTTPRequestHandler() {};
    void redirectHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};
