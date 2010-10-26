#ifndef ezio__hpp_
#define ezio__hpp_

#include "Runtime_Error.hpp"

namespace ezio
{

class Bind_Failure
  : public Runtime_Error
{
public:
  Bind_Failure(
      std::string const & msg);
};

}

#endif // ezio__hpp_
