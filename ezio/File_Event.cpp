#include "File_Event.hpp"

ezio::File_Event::
File_Event(
    File_Event_Enum event1,
    File_Event_Enum event2,
    File_Event_Enum event3)
  : events_(
      static_cast<int>(event1) |
      static_cast<int>(event2) |
      static_cast<int>(event3))
{
}

ezio::File_Event::
File_Event(
    int events)
  : events_(events)
{
}

bool
ezio::File_Event::
read() const
{
  return events_ & static_cast<int>(READ);
}

bool
ezio::File_Event::
write() const
{
  return events_ & static_cast<int>(WRITE);
}

