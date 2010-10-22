#include "ezio/TCP_Server.hpp"

int main()
{
  using namespace ezio;

  TCP_Server server(4242);
  TCP_Socket sock(server.accept());
}

