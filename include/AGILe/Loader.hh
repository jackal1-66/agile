#ifndef AGILE_LOADER_HH 
#define AGILE_LOADER_HH

#include "AGILe/Generator.hh"

namespace AGILe { 

  /// @todo Make this a singleton class with automatic init and finalize
  namespace Loader {
    void initialize();
    std::vector<std::string> getAvailableGens();
    void loadGenLibs(const std::string& genname);
    Generator* createGen();
    void destroyGen(Generator* gen);
    void finalize();
  } 

}

#endif
