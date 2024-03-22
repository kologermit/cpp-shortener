#pragma once
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "../LinkHandler/LinkHandler.hpp"

using namespace Poco;
using namespace Poco::Net;

class LinkHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
	{
		return new LinkHandler;
	}
};