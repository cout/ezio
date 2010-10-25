#ifndef ezio__Libevent_Reactor__hpp_
#define ezio__Libevent_Reactor__hpp_

#include "Reactor.hpp"

#include <ev.h>

namespace ezio
{

class Libev_Reactor
  : public Reactor
{
public:
  Libev_Reactor();

  virtual void run();

  virtual void stop();

  virtual void * io_add(
      File & file,
      File_Callback & file_callback,
      File_Event file_event);

  virtual void io_remove(
      void * key);

private:
  struct ev_loop * loop_;
};

} // ezio

#endif // ezio__Libevent_Reactor__hpp_
