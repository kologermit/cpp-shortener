cmake_minimum_required(VERSION 3.15)
project(API)

include_directories(.)

find_package(Poco REQUIRED)
find_package(GTest REQUIRED)

add_executable(API 
    src/main.cpp 
    src/ApiWebServer/HandlerFactory/HandlerFactory.cpp 
    src/ApiWebServer/HandlerFactory/LinkHandler/LinkHandler.cpp 
    src/ApiWebServer/HandlerFactory/RedirectHandler/RedirectHandler.cpp 
    src/ApiWebServer/ApiWebServer.cpp
    src/Database/Database.cpp
)
target_link_libraries(API Poco::Poco)
target_link_libraries(API gtest::gtest)