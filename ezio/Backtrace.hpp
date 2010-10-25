#ifndef ezio__Backtrace__hpp_
#define ezio__Backtrace__hpp_

#include <string>
#include <vector>

namespace ezio
{

class Backtrace
{
public:
  explicit Backtrace(size_t ignore_frames = 1);

  typedef std::string Location;
  typedef std::vector<Location> Locations;

  Locations const & locations() const { return locations_; }

private:
  Location demangle_location(Location const & location) const;

private:
  Locations locations_;
};

Backtrace backtrace();

} // namespace ezio

#endif // ezio__Backtrace__hpp_

