#include "TCP_Server.hpp"
#include "Bind_Failure.hpp"
#include "System_Exception.hpp"
#include "Addrinfo.hpp"

#include <sstream>

#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>

ezio::TCP_Server::
TCP_Server(File const & file)
  : TCP_Socket(file)
{
}

ezio::TCP_Server::
~TCP_Server()
{
}

ezio::TCP_Server::
TCP_Server(
    std::string const & node,
    std::string const & service,
    int backlog)
{
  Addrinfo addrinfo(node, service);
  bind(addrinfo);
  listen(backlog);
}

ezio::TCP_Server::
TCP_Server(
    std::string const & node,
    int port,
    int backlog)
{
  std::stringstream strm;
  strm << port;
  Addrinfo addrinfo(node, strm.str());
  bind(addrinfo);
  listen(backlog);
}

ezio::TCP_Server::
TCP_Server(
    std::string const & service,
    int backlog)
{
  Addrinfo addrinfo("0.0.0.0", service);
  bind(addrinfo);
  listen(backlog);
}

ezio::TCP_Server::
TCP_Server(
    int port,
    int backlog)
{
  std::stringstream strm;
  strm << port;
  Addrinfo addrinfo("0.0.0.0", strm.str());
  bind(addrinfo);
  listen(backlog);
}

ezio::TCP_Server::
TCP_Server(
    Addrinfo const & addrinfo,
    int backlog)
{
  bind(addrinfo);
  listen(backlog);
}

void
ezio::TCP_Server::
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

  throw Bind_Failure("Could not connect");
}

void
ezio::TCP_Server::
listen(int backlog)
{
  int fd = ::listen(this->fd(), backlog);

  if (fd < 0)
  {
    throw System_Exception("listen");
  }
}

ezio::TCP_Socket
ezio::TCP_Server::
accept()
{
  int fd = ::accept(this->fd(), 0, 0);

  if (fd < 0)
  {
    throw System_Exception("accept");
  }

  TCP_Socket sock;
  sock.fdopen(fd);
  return sock;
}

