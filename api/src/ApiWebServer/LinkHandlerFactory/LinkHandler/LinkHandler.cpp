#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/NumberParser.h>
#include "LinkHandler.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace Poco::Util;
using namespace Poco::Net;
using Poco::Net::HTTPResponse;
using Poco::NumberParser;

int LinkHandler::getParamId(const std::string& uri_string) {
    URI uri(uri_string);
    URI::QueryParameters params = uri.getQueryParameters();
    int id = -1;
    for (auto param : params) {
        if (param.first == "id") {
            if (!NumberParser::tryParse(param.second, id)) {
                return -1;
            }
            break;
        }
    }
    return id;
}

void LinkHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response){
    Application& app = Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());
    app.logger().information("Method: %s; URI: %s", request.getMethod(), request.getURI());

    response.setChunkedTransferEncoding(true);
    response.set("Access-Control-Allow-Origin", this->_doc_host); // Разрешение всех источников
    response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    response.set("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Origin, Authorization, Accept");
    const std::string uri_link_create = "/link/create/";
    const std::string uri_link_delete = "/link/delete/";
    const std::string uri_link_get_info = "/link/get_info/";
    std::string method = request.getMethod();
    std::string uri = request.getURI();
    if (method == "OPTIONS") {
        response.setStatus(HTTPResponse::HTTP_OK);
        response.send() << "success";
    }
    if (method == "POST" && uri.substr(0, uri_link_create.size()) == uri_link_create) {
        createHandler(request, response);
        return;
    }
    if (method == "DELETE" && uri.substr(0, uri_link_delete.size()) == uri_link_delete) {
        deleteHandler(request, response);
        return;
    }
    if (method == "GET" && uri.substr(0, uri_link_get_info.size()) == uri_link_get_info) {
        getInfoHandler(request, response);
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
        response.send() << "Param link not found";
        return;
    }
    std::string code;
    for (int i = 0; i < 6; i++) {
        code += char('A' + this->_random_distance(this->_random_generator));
    }

    Database::Link link = this->_database->createLink(code, param_link, this->_host);

    response.send() << link.toJSON();
    response.setStatus(HTTPResponse::HTTP_OK);
}

void LinkHandler::deleteHandler(HTTPServerRequest &request, HTTPServerResponse &response) {
    int id = getParamId(request.getURI());
    if (id == -1) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Invalid id";
        return;
    }
    Database::Link link = this->_database->getLink(id);
    if (link.id == -1) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Link not found";
        return;
    }
    this->_database->deleteLink(link);

    response.send() << link.toJSON();
    response.setStatus(HTTPResponse::HTTP_OK);
}

void LinkHandler::getInfoHandler(HTTPServerRequest &request, HTTPServerResponse &response) {
    int id = getParamId(request.getURI());
    if (id == -1) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Invalid id";
        return;
    }
    Database::Link link = this->_database->getLink(id);
    if (link.id == -1) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Link not found";
        return;
    }
    response.send() << link.toJSON();
    response.setStatus(HTTPResponse::HTTP_OK);
}