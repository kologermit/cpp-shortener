#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

using namespace Poco::Net;

class LinkHandler : public HTTPRequestHandler
{
public:
    void createHandler(HTTPServerRequest &request, HTTPServerResponse &response);
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response);
};