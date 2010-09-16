#include "Getaddrinfo_Exception.hpp"

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

