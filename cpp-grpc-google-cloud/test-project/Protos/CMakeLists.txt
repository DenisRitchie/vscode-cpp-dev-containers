cmake_minimum_required (VERSION 3.24)

project (user-service C CXX)

protobuf_generate_grpc_cpp (UserService.proto)

add_library(user-service STATIC "")

foreach (_target UserService)
  set (hw_proto_srcs "${_grpc_proto_generated_dir}/${_target}.pb.cc")
  set (hw_proto_hdrs "${_grpc_proto_generated_dir}/${_target}.pb.h")
  set (hw_grpc_srcs "${_grpc_proto_generated_dir}/${_target}.grpc.pb.cc")
  set (hw_grpc_hdrs "${_grpc_proto_generated_dir}/${_target}.grpc.pb.h")
  set (hw_grpc_mock_hdrs "${_grpc_proto_generated_dir}/${_target}_mock.grpc.pb.h")
  target_sources (user-service
    PUBLIC
      ${hw_proto_srcs}
      ${hw_proto_hdrs}
      ${hw_grpc_srcs}
      ${hw_grpc_hdrs})
endforeach()

target_link_libraries (user-service
  PUBLIC
    ${_grpc_grpcpp}
    ${_grpc_grpcpp_reflection}
    ${_protobuf_libprotobuf}
)

target_include_directories (user-service PUBLIC ${_grpc_proto_generated_dir})
target_include_directories (user-service PUBLIC ${_grpc_protobuf_wellknown_include_dir})

target_compile_features (user-service PUBLIC cxx_std_20)
