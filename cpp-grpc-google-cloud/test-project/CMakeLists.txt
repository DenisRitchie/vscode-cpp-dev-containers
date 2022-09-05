cmake_minimum_required (VERSION 3.24)

project (grpc-example)

include (Modules/Grpc.cmake)

include_directories (Models)

add_subdirectory (Protos)
add_subdirectory (Client)
add_subdirectory (Server)
