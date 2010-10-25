#include "File.hpp"

#include <unistd.h>

ezio::File::
File()
  : fd_(-1)
{
}

ezio::File::
File(File const & file)
  : fd_(file.fd_)
{
}

ezio::File::
~File()
{
}

void
ezio::File::
close()
{
  if (fd_ >= 0)
  {
    ::close(fd_);
  }
}

void
ezio::File::
fdopen(int fd)
{
  if (fd_ >= 0)
  {
    close();
  }

  fd_ = fd;
}

