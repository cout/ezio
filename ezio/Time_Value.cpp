#include "Time_Value.hpp"

ezio::Time_Value::
Time_Value(
    Seconds sec,
    Nanoseconds nsec)
  : sec_(sec)
  , nsec_(nsec)
{
  normalize();
}

ezio::Time_Value::
Time_Value(double sec)
  : sec_(sec)
  , nsec_((sec_ - sec) * (1*1000*1000*1000))
{
  normalize();
}

ezio::Time_Value::
operator struct timeval() const
{
  struct timeval tv;
  tv.tv_sec = sec_;
  tv.tv_usec = usec();
  return tv;
}

ezio::Time_Value::
operator struct timespec() const
{
  struct timespec ts;
  ts.tv_sec = sec_;
  ts.tv_nsec = nsec_;
  return ts;
}

void
ezio::Time_Value::
normalize()
{
  sec_ += nsec_ / (1*1000*1000*1000);
  nsec_ = nsec_ % (1*1000*1000*1000);

  if (sec_ > 0 and nsec_ < 0)
  {
    sec_ -= 1;
    nsec_ += (1*1000*1000*1000);
  }
  else if (sec_ < 0 and nsec_ > 0)
  {
    sec_ += 1;
    nsec_ -= (1*1000*1000*1000);
  }
}

double
ezio::Time_Value::
as_double() const
{
  double d = sec_;
  d += static_cast<double>(nsec_) / (1*1000*1000*1000);
}

