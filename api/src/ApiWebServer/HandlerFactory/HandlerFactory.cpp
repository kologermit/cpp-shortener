#include "HandlerFactory.hpp"
#include "../ApiWebServer.hpp"
#include "StandartHandler.hpp"
#include "RedirectHandler/RedirectHandler.hpp"
#include "StandartHeadersProxyHandler.hpp"
#include <regex>

HTTPRequestHandler* HandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    Application& app = Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());
    app.logger().information("Method: %s; URI: %s", request.getMethod(), request.getURI());
    const std::string link_path = "/link/";
    std::string uri = request.getURI();
    if (uri.substr(0, link_path.size()) == link_path) {
        return new StandartHeadersProxyHandler(new LinkHandler(this->_database));
    }
    std::string code = request.getURI().substr(0, 8);
    if (request.getMethod() == "GET" && std::regex_match(code, std::regex("^/[A-Z]{6}/$"))) {
        return new StandartHeadersProxyHandler(new RedirectHandler(this->_database, code));
    }
    return new StandartHeadersProxyHandler(new StandartHandler());
}