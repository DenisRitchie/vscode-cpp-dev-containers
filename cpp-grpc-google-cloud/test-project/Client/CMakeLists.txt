cmake_minimum_required (VERSION 3.24)

project (grpc-client C CXX)

find_package (asio-grpc REQUIRED)

set (Boost_NO_WARN_NEW_VERSIONS ON)
find_package (Boost 1.80.0 REQUIRED COMPONENTS thread context coroutine)

# link_directories (${Boost_LIBRARY_DIRS})
# include_directories (${Boost_INCLUDE_DIRS})

asio_grpc_protobuf_generate (
  GENERATE_GRPC GENERATE_MOCK_CODE
  OUT_VAR "ASIO_GRPC_OBJECT_PROTO_SOURCES"
  OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated"
  PROTOS "${CMAKE_SOURCE_DIR}/Protos/UserService.proto"
)

function(asio_grpc_add_object_proto_target _asio_grpc_name)
    add_library(${_asio_grpc_name} OBJECT)
    target_sources(${_asio_grpc_name} PRIVATE ${ASIO_GRPC_OBJECT_PROTO_SOURCES})
    target_link_libraries(${_asio_grpc_name} PUBLIC protobuf::libprotobuf)
    target_include_directories(${_asio_grpc_name} SYSTEM PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/generated")
endfunction()

asio_grpc_add_object_proto_target(asio-grpc-object-protos)
target_compile_features(asio-grpc-object-protos PUBLIC cxx_std_20)

add_executable (grpc-client Main.cpp)

target_link_libraries (grpc-client
  PRIVATE
    # user-service
    asio-grpc::asio-grpc
    asio-grpc-object-protos
    Boost::boost
    Boost::thread
    Boost::context
    Boost::coroutine
)

target_compile_options (grpc-client PUBLIC -fpermissive )

target_compile_features (grpc-client PUBLIC cxx_std_20)
