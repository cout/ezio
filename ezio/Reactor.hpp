#ifndef ezio__Reactor__hpp_
#define ezio__Reactor__hpp_

#include "File.hpp"
#include "File_Event.hpp"
#include "Not_Copyable.hpp"
#include "Time_Value.hpp"
#include "PID.hpp"

#include <functional>

namespace ezio
{

class Reactor
  : private Not_Copyable
{
public:
  typedef void * Event_Key;

  Reactor();

  virtual ~Reactor();

  virtual void run() = 0;

  virtual void stop() = 0;

  struct File_Callback
    : public std::binary_function<File, File_Event, void>
  {
    virtual void operator()(File &, File_Event) = 0;
  };

  Event_Key io_add(
      File & file,
      File_Callback & file_callback,
      File_Event::File_Event_Enum event1,
      File_Event::File_Event_Enum event2 = File_Event::NONE,
      File_Event::File_Event_Enum event3 = File_Event::NONE);

  virtual Event_Key io_add(
      File & file,
      File_Callback & file_callback,
      File_Event file_event) = 0;

  virtual void io_remove(
      Event_Key key) = 0;

  struct Timer_Callback
  {
    virtual void operator()() = 0;
  };

  virtual void * timer_add(
      Timer_Callback & timer_callback,
      Time_Value delay,
      Time_Value repeat) = 0;

  PID fork();

protected:
  virtual void forked(PID pid);
};

} // ezio

#endif // ezio__Reactor__hpp_
