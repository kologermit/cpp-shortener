cmake_minimum_required(VERSION 3.15)
project(API)

find_package(Poco REQUIRED)

add_executable(API src/main.cpp src/ApiWebServer/LinkHandler/LinkHandler.cpp src/ApiWebServer/ApiWebServer.cpp)
target_link_libraries(API Poco::Poco)

add_executable(SQLITE src/sqlite.cpp)
target_link_libraries(SQLITE Poco::Poco)

# add_executable(SQLITE src)