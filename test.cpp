#include "ezio.hpp"

int main()
{
  TCPSocket sock(TCPSocket::connect("google.com", 80));
}

