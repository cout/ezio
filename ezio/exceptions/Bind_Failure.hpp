#ifndef ezio__Bind_Failure__hpp_
#define ezio__Bind_Failure__hpp_

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

} // ezio

#endif // ezio__Bind_Failure__hpp_
