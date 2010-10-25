#include "TCP_Socket.hpp"
#include "Addrinfo.hpp"

ezio::TCP_Socket::
TCP_Socket()
{
}

ezio::TCP_Socket::
TCP_Socket(File const & file)
  : Socket(file)
{
}

ezio::TCP_Socket::
~TCP_Socket()
{
}

ezio::TCP_Socket
ezio::TCP_Socket::
connect(
    std::string const & node,
    std::string const & service)
{
  TCP_Socket sock;
  sock.Socket::connect(node, service);
  return sock;
}

ezio::TCP_Socket
ezio::TCP_Socket::
connect(
    std::string const & node,
    int port)
{
  TCP_Socket sock;
  sock.Socket::connect(node, port);
  return sock;
}

ezio::TCP_Socket
ezio::TCP_Socket::
connect(
    Addrinfo const & addrinfo)
{
  TCP_Socket sock;
  sock.Socket::connect(addrinfo);
  return sock;
}

