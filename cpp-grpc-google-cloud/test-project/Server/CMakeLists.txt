cmake_minimum_required (VERSION 3.24)

project (grpc-server C CXX)

add_executable (grpc-server Main.cpp)

target_link_libraries(grpc-server PRIVATE user-service)

target_compile_features(grpc-server PUBLIC cxx_std_20)
