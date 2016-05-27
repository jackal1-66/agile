#ifndef AGILE_CHARYBDIS_HH 
#define AGILE_CHARYBDIS_HH 

#include "AGILe/Generator.hh"
#include "AGILe/Charybdis/CharybdisWrapper.hh"

namespace AGILe {


  /// Abstract base class for Charybdis interface
  /// @author Andy Buckley
  class Charybdis : public Generator {
  public:
    /// Standard constructor
    Charybdis() { }
    
    /// Destructor
    ~Charybdis() { }

    // /// Make sure that generic setParam is visible.
    // using Generator::setParam;

    /// Pass a parameter to the generator
    bool setParam(const string& name, const string& value);

    // Reqd for compilation
    void finalize() { }
    void setGenSpecificInitialState(int, double, int, double) { }
  };
  

}

#endif
