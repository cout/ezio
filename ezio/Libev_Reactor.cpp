#include "Libev_Reactor.hpp"

#include <stdexcept>
#include <memory>

extern "C"
void
ezio_libev_file_callback(EV_P_ ev_io * watcher, int revents);

namespace ezio
{

namespace
{

struct Libev_Io_Watcher
{
  Libev_Io_Watcher(File & file, Reactor::File_Callback & callback, int revents)
    : file_(file)
    , callback_(callback)
  {
    ev_io_init(&io_, ezio_libev_file_callback, file.fd(), revents);
    io_.data = static_cast<void *>(this);
  }

  void start(struct ev_loop * loop)
  {
    ev_io_start(loop, &io_);
  }

  void stop(struct ev_loop * loop)
  {
    ev_io_stop(loop, &io_);
  }

  static Libev_Io_Watcher * from_ev_io(ev_io * io)
  {
    return static_cast<Libev_Io_Watcher *>(io->data);
  }

  File file_;
  Reactor::File_Callback & callback_;
  ev_io io_;
};

} // namespace

} // ezio

extern "C"
void
ezio_libev_file_callback(EV_P_ ev_io * io, int revents)
{
  ezio::Libev_Io_Watcher * watcher = ezio::Libev_Io_Watcher::from_ev_io(io);
  watcher->callback_(watcher->file_); // TODO
}

ezio::Libev_Reactor::
Libev_Reactor()
  : loop_(ev_default_loop(EVFLAG_AUTO)) // TODO: support more than one event loop per app
{
}

namespace
{

int libev_event_type(ezio::File_Event_Enum file_event)
{
  switch(file_event)
  {
    case ezio::File_Event::NONE: return 0;
    case ezio::File_Event::READ: return EV_READ;
    case ezio::File_Event::WRITE: return EV_WRITE;
    default: throw std::invalid_argument("invalid file event");
  }
}

} // namespace

void
ezio::Libev_Reactor::
run()
{
  ev_loop(loop_, 0);
}

void
ezio::Libev_Reactor::
stop()
{
  ev_unloop(loop_, EVUNLOOP_ALL);
}

void *
ezio::Libev_Reactor::
io_add(
    File & file,
    File_Callback & file_callback,
    File_Event_Enum event1,
    File_Event_Enum event2,
    File_Event_Enum event3)
{
  int revents =
    libev_event_type(event1) |
    libev_event_type(event2) |
    libev_event_type(event3);

  std::auto_ptr<Libev_Io_Watcher> watcher(
      new Libev_Io_Watcher(file, file_callback, revents));
  watcher->start(loop_);

  void * key = static_cast<void *>(watcher.get());
  watcher.release();
  return key;
}

void
ezio::Libev_Reactor::
io_remove(
    void * key)
{
  Libev_Io_Watcher * watcher = static_cast<Libev_Io_Watcher *>(key);
  watcher->stop(loop_);
  delete watcher;
}

