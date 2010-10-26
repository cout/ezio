#include "File.hpp"
#include "exceptions/System_Exception.hpp"

#include <vector>
#include <algorithm>
#include <cstring>

#include <unistd.h>
#include <sys/uio.h>

#include <iostream> // TODO: remove

class ezio::File::Buffer
{
public:
  static size_t const READ_SIZE = 16384;
  typedef std::vector<char> buffer_type;
  typedef buffer_type::value_type value_type;
  typedef buffer_type::iterator iterator;
  typedef buffer_type::const_iterator const_iterator;

  Buffer()
    : buf_()
    , size_(0)
  {
  }

  size_t fill_from(int fd)
  {
    buf_.resize(size_ + READ_SIZE);
    ssize_t result = ::read(fd, &buf_[size_], READ_SIZE);

    if (result < 0)
    {
      throw System_Exception("read");
    }

    size_ += result;

    return static_cast<size_t>(result);
  }

  size_t size()
  {
    return size_;
  }

  value_type operator[](size_t idx)
  {
    return buf_[idx];
  }

  const_iterator begin() const
  {
    return buf_.begin();
  }

  const_iterator end() const
  {
    return buf_.end();
  }

  bool find(size_t begin_idx, size_t end_idx, char delim, size_t * found_idx)
  {
    const_iterator begin_it = buf_.begin() + begin_idx;
    const_iterator end_it = buf_.begin() + end_idx;

    const_iterator it = std::find(begin_it, end_it, delim);

    if (it != end_it)
    {
      *found_idx = it - begin_it;
      return true;
    }
    else
    {
      return false;
    }
  }

  void erase(size_t begin_idx, size_t end_idx)
  {
    iterator begin_it = buf_.begin() + begin_idx;
    iterator end_it = buf_.begin() + end_idx;

    buf_.erase(begin_it, end_it);

    size_ -= (end_it - begin_it);
  }

private:
  // TODO: not the most efficient way to do I/O (in terms of # of memory
  // allocations), but very simple
  buffer_type buf_;
  size_t size_;
};

ezio::File::
File()
  : fd_(-1)
  , read_buffer_(0)
{
}

ezio::File::
File(File const & file)
  : Shared_Object(file)
  , fd_(file.fd_)
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
  writev(fd_, iov, 2);
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
    bytes_read = read_buffer_->fill_from(fd_);
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
    read_buffer_->fill_from(fd_);
  }

  char c = (*read_buffer_)[0];
  read_buffer_->erase(0, 1);

  return c;
}

