#ifndef ezio__Name_Demangler__hpp_
#define ezio__Name_Demangler__hpp_

#include <string>

std::string
cxx_demangle(
    char const * mangled_name);


inline
std::string
cxx_demangle(
    std::string const & mangled_name)
{
  return cxx_demangle(mangled_name.c_str());
}

#endif // ezio__Name_Demangler__hpp_
