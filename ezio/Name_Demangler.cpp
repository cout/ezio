#include "Name_Demangler.hpp"

#include <cxxabi.h>
#include <cstdlib>
#include <string.h>

std::string
cxx_demangle(
    char const * mangled_name)
{
  struct Helper
  {
    Helper(
        char const * mangled_name)
      : name_(0)
    {
      int status = 0;
      name_ = abi::__cxa_demangle(mangled_name, 0, 0, &status);
      if (name_ == 0)
      {
        name_ = strdup(mangled_name);
      }
    }

    ~Helper()
    {
      std::free(name_);
    }

    char * name_;

  private:
    Helper(Helper const &);
    void operator=(Helper const &);
  };

  Helper helper(mangled_name);
  return helper.name_;
}


