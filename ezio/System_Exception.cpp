#include "System_Exception.hpp"

System_Exception::
System_Exception(int errno)
  : errno_(errno)
{
}

char const *
System_Exception::
what() const throw()
{
  // TODO: use strerror_r
  return ::strerror(errno_);
}

