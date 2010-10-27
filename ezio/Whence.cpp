#include "Whence.hpp"

ezio::Whence::
Whence(Whence_Enum whence)
  : whence_(whence)
{
}

ezio::Whence::
Whence(int whence)
  : whence_(static_cast<Whence_Enum>(whence))
{
}

