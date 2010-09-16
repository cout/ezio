#include "Runtime_Error.hpp"

ezio::Runtime_Error::
Runtime_Error(
    std::string const & msg)
  : msg_(msg)
{
}

char const *
ezio::Runtime_Error::
what() const throw()
{
  return msg_.c_str();
}

