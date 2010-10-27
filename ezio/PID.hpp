#ifndef ezio__PID__hpp_
#define ezio__PID__hpp_

#include <unistd.h>

namespace ezio
{

class PID
{
public:
  PID();

  PID(pid_t pid);

  operator pid_t() { return pid_; }

private:
  pid_t pid_;
};

} // ezio

#endif // ezio__PID__hpp_
