#include "File.hpp"
#include "exceptions/System_Exception.hpp"

#include <vector>
#include <algorithm>
#include <cstring>
#include <cerrno>

#include <unistd.h>
#include <fcntl.h>

#include <sys/uio.h>
#include <sys/stat.h>

ezio::File::
File()
  : fd_(-1)
  , read_buffer_(0)
{
}

ezio::File::
File(std::string const & pathname, int flags, File_Mode mode)
  : fd_(-1)
  , read_buffer_(0)
{
  open(pathname, flags, mode);
}

ezio::File::
File(File const & file)
  : fd_(file.fd_)
  , read_buffer_(0)
{
}

ezio::File::
~File()
{
  delete read_buffer_;
}

void
ezio::File::
close()
{
  if (fd() >= 0)
  {
    ::close(fd());
    fd_.set(-1);
  }
}

void
ezio::File::
open(std::string const & pathname, int flags, File_Mode mode)
{
  int result = ::open(pathname.c_str(), flags, mode.value());

  if (result < 0)
  {
    throw System_Exception("open");
  }
}

ezio::File_Offset
ezio::File::
seek(File_Offset offset, Whence whence)
{
  off_t result = ::lseek(fd(), offset, whence);

  if (result == (off_t)-1)
  {
    throw System_Exception("lseek");
  }

  return File_Offset(result);
}

ezio::File_Offset
ezio::File::
tell()
{
  return seek(0, Whence::CUR);
}

void
ezio::File::
fdopen(int fd)
{
  if (this->fd() >= 0)
  {
    close();
  }

  fd_.set(-1);
}

void
ezio::File::
puts(std::string const & line)
{
  puts(line.c_str(), line.length());
}

void
ezio::File::
puts(char const * line)
{
  puts(line, strlen(line));
}

void
ezio::File::
puts(char const * line, size_t bytes)
{
  char newline[] = "\n";
  struct iovec iov[] = {
    { const_cast<char *>(line), bytes },
    { newline, 1 },
  };
  writev(fd(), iov, 2);
}

std::string
ezio::File::
gets()
{
  std::string line;
  getline(line);
  return line;
}

std::string
ezio::File::
gets(char delim)
{
  std::string line;
  getline(line, delim);
  return line;
}

void
ezio::File::
getline(std::string & str)
{
  getline(str, '\n');
}

void
ezio::File::
getline(std::string & str, char delim)
{
  if (!read_buffer_)
  {
    // TODO: should be possible to avoid the allocation, but for now
    // this is easy
    read_buffer_ = new Buffer;
  }

  size_t idx = 0;
  size_t bytes_read = read_buffer_->size();
  size_t found_idx;

  // TODO: should there be a limit to the number of bytes we read to
  // avoid DoS due to out of memory?
  while ((!read_buffer_->find(idx, idx + bytes_read, delim, &found_idx))) 
  {
    idx = read_buffer_->size();
    bytes_read = read_buffer_->fill_from(fd());
  }

  str.assign(read_buffer_->begin(), read_buffer_->begin() + found_idx);
  read_buffer_->erase(0, found_idx);
}

char
ezio::File::
getc()
{
  if (!read_buffer_)
  {
    // TODO: should be possible to avoid the allocation, but for now
    // this is easy
    read_buffer_ = new Buffer;
  }

  while (read_buffer_->size() == 0)
  {
    read_buffer_->fill_from(fd());
  }

  char c = (*read_buffer_)[0];
  read_buffer_->erase(0, 1);

  return c;
}

bool
ezio::File::
isatty()
{
  int result = ::isatty(fd());

  if(result == 1)
  {
    return true;
  }
  else
  {
    if (errno == EINVAL)
    {
      return false;
    }
    else
    {
      throw System_Exception("isatty");
    }
  }
}

void
ezio::File::
finalize(int fd)
{
  // TODO: duplicated with File::close()
  if (fd >= 0)
  {
    ::close(fd);
  }
}

