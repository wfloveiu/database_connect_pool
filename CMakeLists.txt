cmake_minimum_required(VERSION 3.10)
project(Test)
set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -g")
# SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" SRC)

add_executable(test ${SRC})

# 链接mysql动态库
target_link_libraries(test mysqlclient jsoncpp)