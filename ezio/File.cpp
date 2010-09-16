#include "File.hpp"

#include <unistd.h>

File::
File()
  : fd_(-1)
{
}

void
File::
close()
{
  if (fd_ >= 0)
  {
    ::close(fd_);
  }
}

void
File::
fdopen(int fd)
{
  if (fd_ >= 0)
  {
    close();
  }

  fd_ = fd;
}

