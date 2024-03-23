#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Environment.h>
#include <Poco/URI.h>
#include "../../../Database/Database.hpp"
#include <memory>
#include <random>

using namespace Poco::Net;
using Poco::Environment;
using Poco::URI;

class LinkHandler : public HTTPRequestHandler
{
    std::shared_ptr<Database> _database;
    std::random_device _random_device;
    std::mt19937 _random_generator;
    std::uniform_int_distribution<int> _random_distance;
    std::string _host;
    std::string _doc_host;
    static int getParamId(const std::string& uri_string);
public:
    LinkHandler(
        std::shared_ptr<Database> database
    ): 
        _database(database), 
        _random_generator(this->_random_device()), 
        _random_distance(0, 25), 
        _host(Environment::get("HOST", "http://localhost:8000")),
        _doc_host(Environment::get("DOC_HOST", "http://localhost:8001")),
        HTTPRequestHandler() {};
    void createHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void deleteHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void getInfoHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};