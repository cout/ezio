#include "Exception.hpp"

#include "boost/foreach.hpp"

#include <sstream>

ezio::Exception::
Exception()
  : std::runtime_error("")
  , backtrace_(2)
  , what_()
{
}

ezio::Exception::
Exception(
    std::string const & msg)
  : std::runtime_error(msg)
  , backtrace_(2)
  , what_()
{
}


ezio::Exception::
~Exception() throw()
{
}


char const *
ezio::Exception::
what() const throw()
{
  if (what_ != "")
  {
    return what_.c_str();
  }

  std::stringstream strm;

  strm << std::runtime_error::what() << std::endl;

  BOOST_FOREACH(Backtrace::Location const & loc, backtrace_.locations())
  {
    strm << "    from " << loc << std::endl;
  }

  what_ = strm.str();
  return what_.c_str();
}

