#ifndef ezio__File__hpp_
#define ezio__File__hpp_

#include "Shared_Object.hpp"

#include <string>

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

  std::string getline();
  std::string getline(char delim);
  void getline(std::string & str);
  void getline(std::string & str, char delim);

private:
  int fd_;

  class Buffer;
  Buffer * buffer_;
};

} // ezio

#endif // ezio__File__hpp_

