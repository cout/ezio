#include "TCP_Socket.hpp"

TCP_Socket
TCP_Socket::
connect(
    std::string const & node,
    std::string const & service)
{
  TCP_Socket sock;
  sock.Socket::connect(node, service);
  return sock;
}

TCP_Socket
TCP_Socket::
connect(
    std::string const & node,
    int port)
{
  TCP_Socket sock;
  sock.Socket::connect(node, port);
  return sock;
}

TCP_Socket
TCP_Socket::
connect(
    Addrinfo const & addrinfo)
{
  TCP_Socket sock;
  sock.Socket::connect(addrinfo);
  return sock;
}

