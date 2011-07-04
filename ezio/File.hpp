#ifndef ezio__File__hpp_
#define ezio__File__hpp_

#include "Shared_Object.hpp"
#include "File_Mode.hpp"
#include "File_Offset.hpp"
#include "Whence.hpp"

#include <string>

namespace ezio
{

class Read_Buffer;

class File
{
public:
  File();
  File(std::string const & pathname, int flags, File_Mode mode = 0777);
  File(File const & file);

  virtual ~File();

  void open(std::string const & pathname, int flags, File_Mode mode = 0777);

  virtual void close();

  File_Offset seek(File_Offset offset, Whence whence);

  File_Offset tell();

  int fd() const { return fd_.get(); }

  void fdopen(int fd);

  size_t write(char const * buf, size_t count);

  void puts(std::string const & line);
  void puts(char const * line);
  void puts(char const * line, size_t bytes);

  std::string gets();
  std::string gets(char delim);

  void getline(std::string & str);
  void getline(std::string & str, char delim);

  char getc();

  bool isatty();

  static void finalize(int fd);

private:
  Shared_Object<int, File> fd_;

  Read_Buffer * read_buffer_;
};

} // ezio

#endif // ezio__File__hpp_

