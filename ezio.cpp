#include "sock.hpp"

#include <cstring>
#include <sstream>

#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>

#include <iostream>

System_Exception::
System_Exception(int errno)
  : errno_(errno)
{
}

Runtime_Error::
Runtime_Error(
    std::string const & msg)
  : msg_(msg)
{
}

char const *
Runtime_Error::
what() const throw()
{
  return msg_.c_str();
}

Connection_Failure::
Connection_Failure(
    std::string const & msg)
  : Runtime_Error(msg)
{
}

char const *
System_Exception::
what() const throw()
{
  // TODO: use strerror_r
  return ::strerror(errno_);
}

Getaddrinfo_Exception::
Getaddrinfo_Exception(int errno)
  : errno_(errno)
{
}

char const *
Getaddrinfo_Exception::
what() const throw()
{
  return ::gai_strerror(errno_);
}

Addrinfo::
Addrinfo(
    std::string const & node,
    std::string const & service)
{
  int s = ::getaddrinfo(node.c_str(), service.c_str(), 0, &addrinfo_);
  if (s != 0)
  {
    throw Getaddrinfo_Exception(s);
  }
}

void
Addrinfo::
close()
{
  ::freeaddrinfo(addrinfo_);
}

Shared_Object::
Shared_Object()
  : prev_(this)
  , next_(this)
{
}

Shared_Object::
~Shared_Object()
{
  prev_->next_ = next_;
  next_->prev_ = prev_;

  if (prev_ == next_)
  {
    close();
  }
}

Shared_Object &
Shared_Object::
operator=(
    Shared_Object const & rhs)
{
  Shared_Object tmp(rhs);
  swap(tmp);
  return *this;
}

void
Shared_Object::
swap(
    Shared_Object & shared_object)
{
  std::swap(prev_, shared_object.prev_);
  std::swap(next_, shared_object.next_);
}

Shared_Object::
Shared_Object(
    Shared_Object const & shared_object)
{
  prev_ = shared_object.prev_;
  next_ = &shared_object;
  shared_object.prev_ = this;
}

File::
File()
  : fd_(-1)
{
}

void
File::
close()
{
  if (fd_ >= 0)
  {
    ::close(fd_);
  }
}

void
File::
fdopen(int fd)
{
  if (fd_ >= 0)
  {
    close();
  }

  fd_ = fd;
}

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

TCPSocket
TCPSocket::
connect(
    std::string const & node,
    std::string const & service)
{
  TCPSocket sock;
  sock.Socket::connect(node, service);
  return sock;
}

TCPSocket
TCPSocket::
connect(
    std::string const & node,
    int port)
{
  TCPSocket sock;
  sock.Socket::connect(node, port);
  return sock;
}

TCPSocket
TCPSocket::
connect(
    Addrinfo const & addrinfo)
{
  TCPSocket sock;
  sock.Socket::connect(addrinfo);
  return sock;
}

