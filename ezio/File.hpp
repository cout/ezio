#ifndef ezio__File__hpp_
#define ezio__File__hpp_

namespace ezio
{

class File
  : public Shared_Object
{
public:
  File();

  virtual void close();

  int fd() const { return fd_; }

  void fdopen(int fd);

private:
  int fd_;
};

}

#endif // ezio__File__hpp_

