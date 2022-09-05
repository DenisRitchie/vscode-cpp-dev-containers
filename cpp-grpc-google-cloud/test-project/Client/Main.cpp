#include "UserService.grpc.pb.h"

#include <agrpc/asio_grpc.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <boost/format.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace asio = boost::asio;

uint32_t GenerateId()
{
  static uint32_t Id = 0;
  return ++Id;
}

int32_t main(int32_t argc, char *argv[])
{
  const std::string server_address{"localhost:5001"};

  dev_container::cpp::UserService::Stub stub{
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials())};
  agrpc::GrpcContext grpc_context{std::make_unique<grpc::CompletionQueue>()};

  grpc::Status status;

  auto spawn_lambda = [&]() -> asio::awaitable<void>
  {
    grpc::ClientContext client_context;

    dev_container::cpp::UserRequest request;
    request.mutable_user()->set_user_id(GenerateId());
    request.mutable_user()->set_user_name(
        "UserName: " + std::to_string(request.user().user_id()));
    request.mutable_user()->set_email("Email@test.com");
    request.mutable_user()->set_user_type(
        static_cast<dev_container::cpp::User::UserType>(
            request.user().user_id() % 2));

    const auto reader =
        agrpc::request(&dev_container::cpp::UserService::Stub::AsyncCreateUser,
                       stub, client_context, request, grpc_context);
    dev_container::cpp::User response;

    co_await agrpc::finish(reader, response, status, asio::use_awaitable);
  };

  asio::co_spawn(grpc_context, spawn_lambda, asio::detached);
  asio::co_spawn(grpc_context, spawn_lambda, asio::detached);
  asio::co_spawn(grpc_context, spawn_lambda, asio::detached);
  asio::co_spawn(grpc_context, spawn_lambda, asio::detached);
  asio::co_spawn(grpc_context, spawn_lambda, asio::detached);

  asio::co_spawn(
      grpc_context,
      [&]() -> asio::awaitable<void>
      {
        grpc::ClientContext client_context;

        const auto reader = agrpc::request(
            &dev_container::cpp::UserService::Stub::AsyncListUsers, stub,
            client_context, google::protobuf::Empty{}, grpc_context);

        co_await [&]() -> asio::awaitable<void>
        {
          dev_container::cpp::UserResponse response;
          co_await agrpc::finish(reader, response, status, asio::use_awaitable);

          for (const auto &user : response.users())
          {
            std::cout << boost::format("UserId: %1% \nUserName: %2% \nEmail: %3%") % user.user_id() % user.user_name() % user.email() % user.UserType_Name(user.user_type()) << std::endl;
          }
        }();
      },
      asio::detached);

  grpc_context.run();

  return EXIT_SUCCESS;
}
