cmake_minimum_required(VERSION 3.15)
project(API)

include_directories(.)

find_package(Poco REQUIRED)

add_executable(API 
    src/main.cpp 
    src/ApiWebServer/LinkHandlerFactory/LinkHandler/LinkHandler.cpp 
    src/ApiWebServer/ApiWebServer.cpp
    src/Database/Database.cpp
)
target_link_libraries(API Poco::Poco)

# add_executable(SQLITE 
#     src/test.cpp
#     src/Database/Database.cpp
# )
# target_link_libraries(SQLITE Poco::Poco)

# add_executable(SQLITE src)