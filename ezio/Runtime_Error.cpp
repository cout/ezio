#include "Runtime_Error.hpp"

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

