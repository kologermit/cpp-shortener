#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/DateTime.h>
#include "RedirectHandler.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace Poco::Net;
using Poco::DateTime;

void RedirectHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response){
    std::string method = request.getMethod();
    if (method == "OPTIONS") {
        response.setStatus(HTTPResponse::HTTP_OK);
        response.send() << "Success";
        return;
    }
    redirectHandler(request, response);
}

void RedirectHandler::redirectHandler(HTTPServerRequest &request, HTTPServerResponse &response) {
    IDatabase::Link link = this->_database->getLink(this->_code.substr(1, 6));
    if (link.id == -1) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Link not found";
        return;
    }
    if (link.expire_date < DateTime()) {
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << "Link is expired";
        return;
    }
    std::cout << "Redirect..." << std::endl;
    response.setStatus(HTTPResponse::HTTP_FOUND);
    response.set("Location", link.url);
    response.send() << "Redirect to " << link.url;
}