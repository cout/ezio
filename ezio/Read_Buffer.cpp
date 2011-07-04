#include "Read_Buffer.hpp"
#include "exceptions/System_Exception.hpp"

#include <algorithm>

#include <unistd.h>

ezio::Read_Buffer::
Read_Buffer()
  : buf_()
  , size_(0)
{
}

size_t
ezio::Read_Buffer::
fill_from(int fd)
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

size_t
ezio::Read_Buffer::
size()
{
  return size_;
}

ezio::Read_Buffer::value_type
ezio::Read_Buffer::
operator[](size_t idx)
{
  return buf_[idx];
}

ezio::Read_Buffer::const_iterator
ezio::Read_Buffer::
begin() const
{
  return buf_.begin();
}

ezio::Read_Buffer::const_iterator
ezio::Read_Buffer::
end() const
{
  return buf_.end();
}

bool
ezio::Read_Buffer::
find(size_t begin_idx, size_t end_idx, char delim, size_t * found_idx)
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

void
ezio::Read_Buffer::
erase(size_t begin_idx, size_t end_idx)
{
  iterator begin_it = buf_.begin() + begin_idx;
  iterator end_it = buf_.begin() + end_idx;

  buf_.erase(begin_it, end_it);

  size_ -= (end_it - begin_it);
}

