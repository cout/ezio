#ifndef ezio__System_Exception__hpp_
#define ezio__System_Exception__hpp_

#include "Exception.hpp"

namespace ezio
{

class System_Exception
  : public Exception
{
public:
  System_Exception(
      char const * function);

  System_Exception(
      char const * function,
      int errno_value);

  virtual char const * what() const throw();

private:
  char const * function_;
  int errno_;
};

} // ezio

#endif // ezio__System_Exception__hpp_

