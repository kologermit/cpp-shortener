#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>

#include <memory>
#include <random>

using namespace Poco::Net;

class StandartHandler : public HTTPRequestHandler
{
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
        response.send() << "Method not found";
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
    };
};