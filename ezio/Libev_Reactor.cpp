#include "Libev_Reactor.hpp"

namespace
{

class Libev_Io_Data
{
public:
  File_Callback callback;
}

} // namespace

extern "C"
ezio_libev_file_callback(EV_P_ evio * watcher, int revents)
{
  Libev_Io_Data * data = static_cast<Libev_Io_Data *>(watcher->data);
  data.callback(); // TODO
}

ezio::Libev_Reactor::
Libev_Reactor()
{
}

namespace
{

int libev_event_type(ezio::File_Event file_event)
{
  switch(file_event)
  {
    case FE_NONE: return 0;
    case FE_READ: return EV_READ;
    case FE_WRITE: return EV_WRITE;
    default: throw std::invalid_argument("invalid file event");
  }
}

} // namespace

void
ezio::Libev_Reactor::
stop()
{
  ev_unloop(); // TODO
}

void
ezio::Libev_Reactor::
io_add(
    File file,
    File_Callback file_callback,
    File_Event event1,
    File_Event event2 = FE_NONE,
    File_Event event3 = FE_NONE)
{
  int revents =
    libev_event_type(event1) |
    libev_event_type(event2) |
    libev_event_type(event3);

  ev_io watcher; // TODO: allocate
  ev_io_init(&watcher, ezio_libev_file_callback, file.fd(), revents);
}

