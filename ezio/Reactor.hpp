#ifndef ezio__Reactor__hpp_
#define ezio__Reactor__hpp_

#include "File.hpp"

namespace ezio
{

enum File_Event
{
  FE_NONE,
  FE_READ,
  FE_WRITE,
};

class Reactor
{
public:
  typedef std::unary_function<void, File> File_Callback;
};

} // ezio

#endif // ezio__Reactor__hpp_
