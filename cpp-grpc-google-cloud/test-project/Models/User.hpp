#ifndef F0B2BAA6_DBD7_4BBF_BCFD_1DA23B6EC5F3
#define F0B2BAA6_DBD7_4BBF_BCFD_1DA23B6EC5F3

#include <string>
#include <inttypes.h>

enum struct UserType : int32_t
{
  Admin = 0,
  Standard = 1
};

struct User
{
  int32_t UserId;
  std::string UserName;
  std::string Email;
  UserType Type;
};

#endif /* F0B2BAA6_DBD7_4BBF_BCFD_1DA23B6EC5F3 */
