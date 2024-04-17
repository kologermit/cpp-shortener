#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "src/IDatabase.hpp"
#include <memory>
#include <random>

using namespace Poco::Net;

class RedirectHandler : public HTTPRequestHandler
{
    std::shared_ptr<IDatabase> _database;
    std::string _code;
public:
    RedirectHandler(
        std::shared_ptr<IDatabase> database,
        std::string& code
    ): 
        _database(database), 
        _code(code),
        HTTPRequestHandler() {};
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};
