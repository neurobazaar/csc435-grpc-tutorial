cmake_minimum_required(VERSION 3.22)

project(sockets
        VERSION 1.0
        DESCRIPTION "C++ Client-Server Sockets Example"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/math_formula.proto)

add_executable(server src/Server.cpp ${PROTO_SRCS})
target_include_directories(server PUBLIC include ${PROTO_HDRS})
target_link_libraries(server ${Protobuf_LIBRARIES})

#add_executable(client src/Client.cpp)
#target_include_directories(client PUBLIC include)