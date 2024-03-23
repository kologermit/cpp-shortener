#include "HandlerFactory.hpp"
#include "../ApiWebServer.hpp"
#include "StandartHandler.hpp"
#include "RedirectHandler/RedirectHandler.hpp"
#include <regex>

HTTPRequestHandler* HandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    Application& app = Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());
    app.logger().information("Method: %s; URI: %s", request.getMethod(), request.getURI());
    const std::string link_path = "/link/";
    std::string uri = request.getURI();
    if (uri.substr(0, link_path.size()) == link_path) {
        return new LinkHandler(this->getDB());
    }
    std::string code = request.getURI().substr(0, 8);
    if (request.getMethod() == "GET" && std::regex_match(code, std::regex("^/[A-Z]{6}/$"))) {
        return new RedirectHandler(this->getDB(), code);
    }
    return new StadartHandler();
}