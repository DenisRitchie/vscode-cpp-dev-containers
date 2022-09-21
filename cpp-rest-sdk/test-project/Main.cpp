#include "CasaLens.hpp"

int main(int argc, char *args[])
{
  if (argc != 2)
  {
    printf(U("Usage: casalens.exe port\n"));
    return -1;
  }

  std::string address = U("http://localhost:");
  address.append(args[1]);

  CasaLens listener(address);
  listener.open().wait();

  std::cout << utility::string_t(U("Listening for requests at: ")) << address << std::endl;

  std::string line;
  std::cout << U("Hit Enter to close the listener.");
  std::getline(std::cin, line);

  listener.close().wait();

  return 0;
}
