#include "File_Mode.hpp"

#include <sys/stat.h>

ezio::File_Mode::
File_Mode(mode_t mode)
  : mode_(mode)
{
}

bool
ezio::File_Mode::
user_read() const
{
  return mode_ & S_IRUSR;
}

bool
ezio::File_Mode::
user_write() const
{
  return mode_ & S_IWUSR;
}

bool
ezio::File_Mode::
user_exec() const
{
  return mode_ & S_IXUSR;
}

bool
ezio::File_Mode::
group_read() const
{
  return mode_ & S_IRGRP;
}

bool
ezio::File_Mode::
group_write() const
{
  return mode_ & S_IWGRP;
}

bool
ezio::File_Mode::
group_exec() const
{
  return mode_ & S_IXGRP;
}

bool
ezio::File_Mode::
others_read() const
{
  return mode_ & S_IROTH;
}

bool
ezio::File_Mode::
others_write() const
{
  return mode_ & S_IWOTH;
}

bool
ezio::File_Mode::
others_exec() const
{
  return mode_ & S_IXOTH;
}

bool ezio::File_Mode::
socket() const
{
  return mode_ & S_IFSOCK;
}

bool ezio::File_Mode::
fifo() const
{
  return mode_ & S_IFIFO;
}

bool ezio::File_Mode::
symlink() const
{
  return mode_ & S_IFLNK;
}

bool ezio::File_Mode::
regfile() const
{
  return mode_ & S_IFREG;
}

bool ezio::File_Mode::
blockdev() const
{
  return mode_ & S_IFBLK;
}

bool ezio::File_Mode::
chardev() const
{
  return mode_ & S_IFCHR;
}

bool ezio::File_Mode::
setuid() const
{
  return mode_ & S_ISUID;
}

bool ezio::File_Mode::
setgid() const
{
  return mode_ & S_ISGID;
}

bool ezio::File_Mode::
sticky() const
{
  return mode_ & S_ISVTX;
}

