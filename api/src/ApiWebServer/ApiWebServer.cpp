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
    HTTPServer srv(new HandlerFactory(this->_database), port);
    srv.start();
    logger().information("HTTP Server started on port %hu.", port);
    waitForTerminationRequest();
    logger().information("Stopping HTTP Server...");
    srv.stop();

    return Application::EXIT_OK;
}