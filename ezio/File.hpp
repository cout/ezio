#ifndef ezio__File__hpp_
#define ezio__File__hpp_

#include "Shared_Object.hpp"

namespace ezio
{

class File
  : public Shared_Object
{
public:
  File();

  File(File const & file);

  virtual ~File();

  virtual void close();

  int fd() const { return fd_; }

  void fdopen(int fd);

private:
  int fd_;
};

} // ezio

#endif // ezio__File__hpp_

