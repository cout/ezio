#ifndef ezio__Libevent_Reactor__hpp_
#define ezio__Libevent_Reactor__hpp_

#include "Reactor.hpp"

namespace ezio
{

class Libev_Reactor
  : public Reactor
{
public:
  Libev_Reactor();

  void stop();

  void io_add(
      File file,
      File_Callback file_callback,
      File_Event event1,
      File_Event event2 = FE_NONE,
      File_Event event3 = FE_NONE);
}

} // ezio

#endif // ezio__Libevent_Reactor__hpp_
