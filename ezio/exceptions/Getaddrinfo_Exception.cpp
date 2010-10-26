#include "Getaddrinfo_Exception.hpp"

#include <netdb.h>

ezio::Getaddrinfo_Exception::
Getaddrinfo_Exception(int errno)
  : errno_(errno)
{
}

char const *
ezio::Getaddrinfo_Exception::
what() const throw()
{
  return ::gai_strerror(errno_);
}

