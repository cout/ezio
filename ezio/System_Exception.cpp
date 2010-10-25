#include "System_Exception.hpp"

#include <string.h>
#include <cerrno>

ezio::System_Exception::
System_Exception(
    char const * function)
  : function_(function)
  , errno_(errno)
{
}

ezio::System_Exception::
System_Exception(
    char const * function,
    int errno_value)
  : function_(function)
  , errno_(errno_value)
{
}

char const *
ezio::System_Exception::
message() const
{
  // TODO: include function_ in the output
  // TODO: use strerror_r
  return ::strerror(errno_);
}

