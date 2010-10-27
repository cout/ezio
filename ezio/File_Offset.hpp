#ifndef ezio__File_Offset__hpp_
#define ezio__File_Offset__hpp_

#include <sys/types.h>

namespace ezio
{

class File_Offset
{
public:
  File_Offset();
  File_Offset(off_t offset);

  off_t value() const { return offset_; }

  operator off_t() const { return offset_; }

private:
  off_t offset_;
};

}

#endif // ezio__File_Offset__hpp_
