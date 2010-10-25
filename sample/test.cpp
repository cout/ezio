#include "ezio/TCP_Socket.hpp"

int main()
{
  using namespace ezio;

  TCP_Socket sock(TCP_Socket::connect("google.com", 80));
}

