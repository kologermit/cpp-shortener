cmake_minimum_required(VERSION 3.15)
project(API)

find_package(Poco REQUIRED)

add_executable(API src/main.cpp)
target_link_libraries(${PROJECT_NAME} Poco::Poco)