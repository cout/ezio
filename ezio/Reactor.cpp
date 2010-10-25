#include "Reactor.hpp"

ezio::Reactor::
Reactor()
{
}

ezio::Reactor::
~Reactor()
{
}

void *
ezio::Reactor::
io_add(
    File & file,
    File_Callback & file_callback,
    File_Event::File_Event_Enum event1,
    File_Event::File_Event_Enum event2,
    File_Event::File_Event_Enum event3)
{
  File_Event file_event(
      event1,
      event2,
      event3);

  return io_add(file, file_callback, file_event);
}

