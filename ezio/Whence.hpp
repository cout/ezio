#ifndef ezio__Whence__hpp_
#define ezio__Whence__hpp_

#include <unistd.h>

namespace ezio
{

class Whence
{
public:
  enum Whence_Enum
  {
    SET = SEEK_SET,
    CUR = SEEK_CUR,
    END = SEEK_END,
  };

  Whence(Whence_Enum whence);

  Whence(int whence);

  Whence_Enum value() const { return whence_; }

  operator int() const { return whence_; }

private:
  Whence_Enum whence_;
};

}

#endif // ezio__Whence__hpp_
