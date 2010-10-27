#ifndef ezio__Time_Value__hpp_
#define ezio__Time_Value__hpp_

#include <time.h>
#include <sys/time.h>

namespace ezio
{

class Time_Value
{
public:
  typedef long Seconds;
  typedef long Microseconds;
  typedef long Nanoseconds;

  Time_Value(
      Seconds sec,
      Nanoseconds usec);

  Time_Value(
      double sec);

  operator struct timeval () const;
  operator struct timespec () const;

  Seconds sec() const { return sec_; }
  Nanoseconds nsec() const { return nsec_; }
  Microseconds usec() const { return nsec_ / 1000; }

  double as_double() const;

private:
  void normalize();

private:
  Seconds sec_;
  Nanoseconds nsec_;
};

} // ezio

#endif // ezio__Time_Value__hpp_
