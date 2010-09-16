#ifndef ezio__hpp_
#define ezio__hpp_

#include "Runtime_Error.hpp"

namespace ezio
{

class Connection_Failure
  : public Runtime_Error
{
public:
  Connection_Failure(
      std::string const & msg);
};

}

#endif // ezio__hpp_
