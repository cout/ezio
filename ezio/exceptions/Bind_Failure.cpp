#include "Bind_Failure.hpp"

ezio::Bind_Failure::
Bind_Failure(
    std::string const & msg)
  : Runtime_Error(msg)
{
}

