#ifndef AGILE_AGILe_HH
#define AGILE_AGILe_HH

// Macro to help with overzealous compiler warnings
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#ifdef LIB_SUFFIX
#define SYSDSO string(LIB_SUFFIX)
#else
#define SYSDSO string(".so")
#endif

// Bring selected STL/Boost classes into the AGILe namespace
#include "AGILe/AGILeSTL.hh"
#include "AGILe/AGILeBoost.hh"

#include "AGILe/Tools/AGILePaths.hh"
#include "AGILe/Tools/Logging.hh"

namespace AGILe {
  /// A function to get the AGILe version string
  std::string version();
}

#endif
