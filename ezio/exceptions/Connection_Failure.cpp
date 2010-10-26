#include "Connection_Failure.hpp"

ezio::Connection_Failure::
Connection_Failure(
    std::string const & msg)
  : Runtime_Error(msg)
{
}

