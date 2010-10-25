#ifndef ezio__Exception__hpp_
#define ezio__Exception__hpp_

#include "Backtrace.hpp"

#include <stdexcept>
#include <string>

namespace ezio
{

class Exception
  : public std::runtime_error
{
public:
  Exception();

  Exception(std::string const & msg);

  virtual ~Exception() throw();

  virtual char const * what() const throw();

private:
  Backtrace backtrace_;
  mutable std::string what_;
};

} // namespace ezio

#endif // ezio__Exception__hpp_

