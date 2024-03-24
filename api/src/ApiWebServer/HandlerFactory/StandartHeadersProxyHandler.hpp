#pragma once
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

#include <memory>

using namespace Poco::Net;

class StandartHeadersProxyHandler: public HTTPRequestHandler {
private:
    std::unique_ptr<HTTPRequestHandler> _requestHandlerPtr;
public:
    StandartHeadersProxyHandler(HTTPRequestHandler* ptr): _requestHandlerPtr(ptr) {};
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) override {
        static std::string _doc_host = Environment::get("DOC_HOST", "http://localhost:8001");
        response.setChunkedTransferEncoding(true);
        response.set("Access-Control-Allow-Origin", _doc_host);
        response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        response.set("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Origin, Authorization, Accept");
        this->_requestHandlerPtr->handleRequest(request, response);
    };
};