#ifndef ezio__File_Event__hpp_
#define ezio__File_Event__hpp_

namespace ezio
{

class File_Event
{
public:
  enum File_Event_Enum
  {
    NONE  = 1 << 0,
    READ  = 1 << 1,
    WRITE = 1 << 2,
  };

  File_Event(
      File_Event_Enum event1 = NONE,
      File_Event_Enum event2 = NONE,
      File_Event_Enum event3 = NONE);

  explicit File_Event(
      int events);

  bool read() const;
  bool write() const;

private:
  int events_;
};

}

#endif // ezio__File_Event__hpp_
