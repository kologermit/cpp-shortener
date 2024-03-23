#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

#include <Poco/Net/HTTPServer.h>
#include "ApiWebServer.hpp"
#include "HandlerFactory/HandlerFactory.hpp"

using namespace Poco;
using namespace Poco::Net;

int ApiWebServer::main(const std::vector<std::string>&)
{
    UInt16 port = 8080;
    HTTPServer srv(new HandlerFactory(this->getDB()), port);
    srv.start();
    logger().information("HTTP Server started on port %hu.", port);
    waitForTerminationRequest();
    logger().information("Stopping HTTP Server...");
    srv.stop();

    return Application::EXIT_OK;
}

std::shared_ptr<Database> ApiWebServer::getDB() {
    return this->_database;
}

void ApiWebServer::setupStandartHeaders(HTTPServerResponse& response) {
    static std::string _doc_host = Environment::get("DOC_HOST", "http://localhost:8001");
    response.setChunkedTransferEncoding(true);
    response.set("Access-Control-Allow-Origin", _doc_host);
    response.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    response.set("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Origin, Authorization, Accept");
}