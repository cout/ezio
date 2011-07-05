#ifndef ezio__Reader__hpp_
#define ezio__Reader__hpp_

#include "File.hpp"

namespace ezio
{

class Reactor;

class Reader
{
public:
  Reader(
      File file,
      Reactor * reactor);

  size_t read(char * buf, size_t buflen);

private:
  File file_;
  Reactor * reactor_;
};

} // namespace ezio

#endif // ezio__Reader__hpp_
