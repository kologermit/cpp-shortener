#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include "LinkHandler.hpp"

using namespace Poco::Util;
using namespace Poco::Net;

void LinkHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response){
    Application& app = Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());
    app.logger().information("Method: %s; URI: %s", request.getMethod(), request.getURI());
    
    response.setChunkedTransferEncoding(true);
    response.set("Access-Control-Allow-Origin", "http://kologermit.ru:8001"); // Разрешение всех источников
    response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    response.set("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Origin, Authorization, Accept");
    const std::string uri_link_create = "/link/create/";
    if (request.getMethod() == "POST" && request.getURI().substr(0, uri_link_create.size()) == uri_link_create) {
        createHandler(request, response);
        return;
    }
    response.send() << "Standart answer";
}

void LinkHandler::createHandler(HTTPServerRequest &request, HTTPServerResponse &response){
    response.send() << "Create answer";
}