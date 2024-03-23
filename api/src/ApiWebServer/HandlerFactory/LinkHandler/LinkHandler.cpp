#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/NumberParser.h>
#include "../../ApiWebServer.hpp"
#include "LinkHandler.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace Poco::Net;
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
    ApiWebServer::setupStandartHeaders(response);
    std::string method = request.getMethod();
    std::string uri = request.getURI();
    if (method == "OPTIONS") {
        response.setStatus(HTTPResponse::HTTP_OK);
        response.send() << "Success";
        return;
    }
    const std::string uri_link_create = "/link/create/";
    const std::string uri_link_delete = "/link/delete/";
    const std::string uri_link_get_info = "/link/get_info/";
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
    response.send() << "Method not found";
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