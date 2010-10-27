#include "PID.hpp"

ezio::PID::
PID()
  : pid_(0)
{
}

ezio::PID::
PID(pid_t pid)
  : pid_(pid)
{
}

