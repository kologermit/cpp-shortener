#pragma once
#include <Poco/Util/ServerApplication.h>

using namespace Poco::Util;

class ApiWebServer : public ServerApplication
{
    void initialize(Application& self)
    {
        loadConfiguration();
        ServerApplication::initialize(self);
    }
    int main(const std::vector<std::string>&);
};