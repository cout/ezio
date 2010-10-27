#include "File_Offset.hpp"

ezio::File_Offset::
File_Offset()
  : offset_(0)
{
}

ezio::File_Offset::
File_Offset(off_t offset)
  : offset_(offset)
{
}
