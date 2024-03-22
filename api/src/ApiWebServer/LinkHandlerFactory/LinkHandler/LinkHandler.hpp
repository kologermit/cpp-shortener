#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../Database/Database.hpp"
#include <memory>

using namespace Poco::Net;

class LinkHandler : public HTTPRequestHandler
{
    std::shared_ptr<Database> _database;
public:
    LinkHandler(std::shared_ptr<Database> database): _database(database), HTTPRequestHandler() {};
    void createHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};