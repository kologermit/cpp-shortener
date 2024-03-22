#include "ApiWebServer/ApiWebServer.hpp"
#include "Database/Database.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv)		
{	
    try 							
    {	
        Database::registerConnector();
        ApiWebServer app(std::shared_ptr<Database>(new Database("db.sqlite3")));					
        return app.run(argc, argv);	
    }								
    catch (std::exception& exc)	
    {
        std::cerr << "Exception: " << std::endl;
        std::cerr << exc.what() << std::endl;	
        return Poco::Util::Application::EXIT_SOFTWARE; 	
    }								
}