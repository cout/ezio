#include "Streambuf.hpp"

ezio::Streambuf::
Streambuf(
    File file)
  : file_(file)
{
}

int
ezio::Streambuf::
overflow(int c)
{
  write_buffer_.push_back(c);

  if (write_buffer_.size() >= WRITE_BUFFER_SIZE)
  {
    sync();
  }
}

int
ezio::Streambuf::
underflow()
{
  // TODO: for now, let the File object do its own buffering
  // TODO: File throws a System_Exception on end of file; we want to
  // return EOF.
  return file_.getc();
}

ezio::Streambuf *
ezio::Streambuf::
setbuf(char * buf, std::streamsize len)
{
  // TODO: ignore this request, for now
  return this;
}

int
ezio::Streambuf::
sync()
{
  if (write_buffer_.size() > 0)
  {
    size_t bytes_written = file_.write(
        &write_buffer_[0],
        WRITE_BUFFER_SIZE);

    write_buffer_.erase(
        write_buffer_.begin() + 0,
        write_buffer_.begin() + bytes_written);
  }
}

