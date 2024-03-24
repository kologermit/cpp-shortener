#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Environment.h>
#include <Poco/URI.h>
#include "src/IDatabase.hpp"
#include <memory>
#include <random>

using namespace Poco::Net;
using Poco::URI;
using Poco::Environment;

class LinkHandler : public HTTPRequestHandler
{
    std::shared_ptr<IDatabase> _database;
    std::random_device _random_device;
    std::mt19937 _random_generator;
    std::uniform_int_distribution<int> _random_distance;
    std::string _host;
    static int getParamId(const std::string& uri_string);
    static std::string LinkToJSON(const IDatabase::Link& link);
public:
    LinkHandler(
        std::shared_ptr<IDatabase> database
    ): 
        _database(database), 
        _random_generator(this->_random_device()), 
        _random_distance(0, 25), 
        _host(Environment::get("HOST", "http://localhost:8000")),
        HTTPRequestHandler() {};
    void createHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void deleteHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void getInfoHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};