#include "Backtrace.hpp"
#include "Regex.hpp"

#include "cxx_demangle.hpp"

#include <sstream>
#include <cstdlib>

#include <execinfo.h>

ezio::Backtrace::
Backtrace(size_t ignore_frames)
  : locations_()
{
  size_t n;
  void * buffer[8192];
  n = ::backtrace((void **)&buffer, sizeof(buffer));

  char * * strings = backtrace_symbols(buffer, n);
  if (!strings)
  {
    // error, but since this object is probably getting constructed in
    // an exceptional case, we don't want to throw another exception and
    // perhaps obscure the real problem so just return
    return;
  }

  for(size_t idx = ignore_frames; idx < n; ++idx)
  {
    locations_.push_back(demangle_location(strings[idx]));
  }

  std::free(strings);
}

ezio::Backtrace::Location
ezio::Backtrace::
demangle_location(Location const & location) const
{
  Regex regex(
      "(.*?)\\((.*?)\\+(.*?)\\)\\s*\\[(.*?)\\]");

  Regex::Match match(4);
  if (regex.match(location, &match))
  {
    std::string filename = match.str(1);
    std::string funcname = cxx_demangle(match.str(2));
    std::string offset = match.str(3);
    std::string addr = match.str(4);

    std::stringstream result;
    result << filename << "(" << funcname << "+" << offset << ")" << " [" << addr << "]";
    return result.str();
  }
  else
  {
    return location;
  }
}

