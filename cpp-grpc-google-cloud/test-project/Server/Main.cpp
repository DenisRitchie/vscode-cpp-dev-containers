#include <iostream>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "UserService.grpc.pb.h"
#include "User.hpp"

#include <list>
#include <type_traits>
#include <string_view>

class UserServiceImpl final : public ::dev_container::cpp::UserService::Service
{
public:
  UserServiceImpl() noexcept = default;
  UserServiceImpl(const UserServiceImpl &) = delete;
  UserServiceImpl(UserServiceImpl &&) = delete;
  UserServiceImpl &operator=(const UserServiceImpl &) = delete;
  UserServiceImpl &operator=(UserServiceImpl &&) = delete;
  virtual ~UserServiceImpl() noexcept = default;

  virtual ::grpc::Status ListUsers(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::dev_container::cpp::UserResponse *response) override
  {
    std::clog << "Get User List of " << m_Users.size() << " Items" << std::endl;

    for (const auto &user : m_Users)
    {
      auto user_response = response->add_users();
      user_response->set_user_id(user.UserId);
      user_response->set_user_name(user.UserName);
      user_response->set_email(user.Email);
      user_response->set_user_type(static_cast<dev_container::cpp::User_UserType>(user.Type));
    }

    return grpc::Status::OK;
  }

  virtual ::grpc::Status CreateUser(::grpc::ServerContext *context, const ::dev_container::cpp::UserRequest *request, ::dev_container::cpp::User *response) override
  {
    if (request->has_user())
    {
      std::clog << "New UserId: " << request->user().user_id() << std::endl;

      m_Users.push_back(User{.UserId = request->user().user_id(),
                             .UserName = request->user().user_name(),
                             .Email = request->user().email(),
                             .Type = static_cast<UserType>(request->user().user_type())});

      response->CopyFrom(request->user());
    }

    return grpc::Status::OK;
  }

private:
  std::list<User> m_Users;
};

int32_t main(int32_t argc, char *argv[])
{
  const std::string server_address{"0.0.0.0:5001"};

  UserServiceImpl user_service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder server_builder;

  // Listen on the given address without any authentication mechanism.
  server_builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  server_builder.RegisterService(&user_service);

  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(server_builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return EXIT_SUCCESS;
}
