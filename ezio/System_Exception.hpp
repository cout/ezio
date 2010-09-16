#ifndef ezio__System_Exception__hpp_
#define ezio__System_Exception__hpp_

#include "Exception.hpp"

namespace ezio
{

class System_Exception
  : public Exception
{
public:
  System_Exception(int errno);

  virtual char const * what() const throw();

private:
  int errno_;
};

}

#endif // ezio__System_Exception__hpp_

