#ifndef ezio__Reactor__hpp_
#define ezio__Reactor__hpp_

#include "File.hpp"
#include "Not_Copyable.hpp"

#include <functional>

namespace ezio
{

namespace File_Event
{

enum File_Event_Enum
{
  NONE,
  READ,
  WRITE,
};

} // File_Event

using File_Event::File_Event_Enum;

class Reactor
  : private Not_Copyable
{
public:
  Reactor();

  virtual ~Reactor();

  virtual void run() = 0;

  virtual void stop() = 0;

  virtual void * io_add(
      File & file,
      File_Callback & file_callback,
      File_Event_Enum event1,
      File_Event_Enum event2 = File_Event::NONE,
      File_Event_Enum event3 = File_Event::NONE) = 0;

  virtual void io_remove(
      void * key) = 0;

  struct File_Callback
    : public std::unary_function<File, void>
  {
    virtual void operator()(File &) = 0;
  };
};

} // ezio

#endif // ezio__Reactor__hpp_
