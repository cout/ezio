#include "Socket.hpp"

#include <sstream>

#include <sys/socket.h>

void
Socket::
connect(
    std::string const & node,
    std::string const & service)
{
  Addrinfo addrinfo(node, service);
  return connect(addrinfo);
}

void
Socket::
connect(
    std::string const & node,
    int port)
{
  std::stringstream strm;
  strm << port;
  Addrinfo addrinfo(node, strm.str());
  return connect(addrinfo);
}

void
Socket::
connect(
    Addrinfo const & addrinfo)
{
  struct addrinfo const * rp;
  for(rp = addrinfo.addrinfo(); rp != 0; rp = rp->ai_next)
  {
    int fd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if (fd < 0)
    {
      continue;
    }

    if (::connect(fd, rp->ai_addr, rp->ai_addrlen) >= 0)
    {
      fdopen(fd);
      return;
    }
  }

  throw Connection_Failure("Could not connect");
}

