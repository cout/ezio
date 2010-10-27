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

  virtual void * timer_add(
      Timer_Callback & timer_callback,
      Time_Value delay,
      Time_Value repeat);

protected:
  virtual void forked(PID pid);

private:
  struct ev_loop * loop_;
};

} // ezio

#endif // ezio__Libevent_Reactor__hpp_
