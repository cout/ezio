#include "Connection_Failure.hpp"

Connection_Failure::
Connection_Failure(
    std::string const & msg)
  : Runtime_Error(msg)
{
}

