#pragma once
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "LinkHandler/LinkHandler.hpp"

#include <memory>

using namespace Poco;
using namespace Poco::Net;

class HandlerFactory : public HTTPRequestHandlerFactory
{
    std::shared_ptr<IDatabase> _database;
    std::shared_ptr<Environment> _env;
public:
    HandlerFactory(
        std::shared_ptr<IDatabase> database
    ): _database(database), HTTPRequestHandlerFactory() {};
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
};