#ifndef ezio__Runtime_Error__hpp_
#define ezio__Runtime_Error__hpp_

#include <string>

#include "Exception.hpp"

namespace ezio
{

class Runtime_Error
  : public Exception
{
public:
  Runtime_Error(
      std::string const & msg);

  char const * what() const throw();

private:
  std::string const & msg_;
};

}

#endif // ezio__Runtime_Error__hpp_

