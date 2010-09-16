#include "System_Exception.hpp"

#include <string.h>

ezio::System_Exception::
System_Exception(int errno)
  : errno_(errno)
{
}

char const *
ezio::System_Exception::
what() const throw()
{
  // TODO: use strerror_r
  return ::strerror(errno_);
}

