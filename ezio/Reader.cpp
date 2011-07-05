#include "Reader.hpp"

#include "Reactor.hpp"
#include "exceptions/System_Exception.hpp"

#include <cerrno>

namespace
{

class Read_Waiter
  : public ezio::Reactor::File_Callback
{
public:
  Read_Waiter(
      ezio::Reactor * reactor,
      ezio::File file,
      char * buf,
      size_t buflen,
      int & error,
      size_t & bytes_read)
    : reactor_(reactor)
    , buf_(buf)
    , buflen_(buflen)
    , error_(error)
    , bytes_read_(bytes_read)
    , event_key_(reactor_->io_add(
            file,
            *this,
            ezio::File_Event::READ))
  {
  }

  ~Read_Waiter()
  {
    reactor_->io_remove(event_key_);
  }

  void read()
  {
    while (bytes_read_ == 0 and not error_)
    {
      reactor_->run();
    }
  }

  void operator()(ezio::File & file, ezio::File_Event event)
  {
    ssize_t result = ::read(file.fd(), buf_ + bytes_read_, buflen_ + bytes_read_);

    if (result < 0)
    {
      error_ = errno;
    }

    bytes_read_ += result;
  }

private:
  ezio::Reactor * reactor_;
  char * buf_;
  size_t buflen_;
  int & error_;
  size_t & bytes_read_;
  ezio::Reactor::Event_Key event_key_;
};

} // namespace

ezio::Reader::
Reader(
    File file,
    Reactor * reactor)
  : file_(file)
  , reactor_(reactor)
{
}

size_t
ezio::Reader::
read(char * buf, size_t buflen)
{
  int error = 0;
  size_t bytes_read = 0;

  Read_Waiter waiter(
      reactor_,
      file_,
      buf,
      buflen,
      error,
      bytes_read);

  waiter.read();

  if (error)
  {
    throw System_Exception("read");
  }
  else
  {
    return bytes_read;
  }
}

