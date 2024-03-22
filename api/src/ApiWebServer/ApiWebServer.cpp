#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

#include "LinkHandlerFactory/LinkHandlerFactory.hpp"
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/ScopedLock.h>
#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>
#include "ApiWebServer.hpp"
#include "LinkHandlerFactory/LinkHandlerFactory.hpp"

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

int ApiWebServer::main(const std::vector<std::string>&)
{
    UInt16 port = 8080;
    HTTPServer srv(new LinkHandlerFactory(this->getDB()), port);
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