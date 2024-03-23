#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/URI.h>
#include <Poco/Environment.h>
#include "LinkHandler.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace Poco::Util;
using namespace Poco::Net;
using Poco::Environment;
using Poco::URI;
using Poco::Net::HTTPResponse;

void LinkHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response){
    Application& app = Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());
    app.logger().information("Method: %s; URI: %s", request.getMethod(), request.getURI());

    response.setChunkedTransferEncoding(true);
    response.set("Access-Control-Allow-Origin", Environment::get("DOC_URL", "http://localhost:8001")); // Разрешение всех источников
    response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    response.set("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Origin, Authorization, Accept");
    const std::string uri_link_create = "/link/create/";
    if (request.getMethod() == "POST" && request.getURI().substr(0, uri_link_create.size()) == uri_link_create) {
        createHandler(request, response);
        return;
    }
    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    response.send() << "404: method not found";
}

void LinkHandler::createHandler(HTTPServerRequest &request, HTTPServerResponse &response){
    URI uri(request.getURI());
    URI::QueryParameters params = uri.getQueryParameters();
    std::string param_link;
    for (auto param : params) {
        if (param.first == "link") {
            param_link = param.second;
            break;
        }
    }
    if (param_link.empty()) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "link not found";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 25);
    std::string code;
    for (int i = 0; i < 6; i++) {
        code += char('A' + dis(gen));
    }

    Database::Link link = this->_database->createLink(code, param_link);

    response.send() << link.toJSON();
    response.setStatus(HTTPResponse::HTTP_OK);
}