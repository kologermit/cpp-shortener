#pragma once
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "LinkHandler/LinkHandler.hpp"

#include <memory>

using namespace Poco;
using namespace Poco::Net;

class HandlerFactory : public HTTPRequestHandlerFactory
{
	std::shared_ptr<Database> _database;
	std::shared_ptr<Environment> _env;
public:
	HandlerFactory(
		std::shared_ptr<Database> database
	): _database(database), HTTPRequestHandlerFactory() {};
	std::shared_ptr<Database> getDB() { return this->_database; }
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
};