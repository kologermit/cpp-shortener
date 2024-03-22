#pragma once
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "LinkHandler/LinkHandler.hpp"

using namespace Poco;
using namespace Poco::Net;

class LinkHandlerFactory : public HTTPRequestHandlerFactory
{
	std::shared_ptr<Database> _database;
public:
	LinkHandlerFactory(std::shared_ptr<Database> database): _database(database), HTTPRequestHandlerFactory() {};
	std::shared_ptr<Database> getDB() { return this->_database; }
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
	{
		return new LinkHandler(this->getDB());
	}
};