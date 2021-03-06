#include "Socket.hpp"
#include "Addrinfo.hpp"
#include "exceptions/Connection_Failure.hpp"
#include "exceptions/Bind_Failure.hpp"

#include <sstream>

#include <netdb.h>

#include <sys/socket.h>

ezio::Socket::
Socket()
{
}

ezio::Socket::
Socket(File file)
  : File(file)
{
}

ezio::Socket::
~Socket()
{
}

void
ezio::Socket::
connect(
    std::string const & node,
    std::string const & service)
{
  Addrinfo addrinfo(node, service);
  return connect(addrinfo);
}

void
ezio::Socket::
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
ezio::Socket::
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

void
ezio::Socket::
bind(
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

    if (::bind(fd, rp->ai_addr, rp->ai_addrlen) >= 0)
    {
      fdopen(fd);
      return;
    }
  }

  // TODO: set SO_REUSEADDR

  throw ezio::Bind_Failure("Could not bind");
}

