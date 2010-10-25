#include "Runtime_Error.hpp"

ezio::Runtime_Error::
Runtime_Error(
    std::string const & msg)
  : Exception(msg)
{
}

