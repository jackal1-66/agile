#ifndef AGILE_ALPGEN_HH 
#define AGILE_ALPGEN_HH

#include "AGILe/Generator.hh"

namespace AGILe {


  /// Abstract base class for AlpGen interface
  /// @author Andy Buckley
  class AlpGen : public Generator {
  public:
    /// Constructor.
    AlpGen() { }
    
    /// Destructor.
    ~AlpGen() { }

    /// Make sure that generic setParam is visible.
    //using Generator::setParam;
    
    /// Pass a parameter to the generator.
    bool setParam(const string& name, const string& value);

    // Reqd for compilation
    void finalize() { }
    void setGenSpecificInitialState(int, double, int, double) { }
  };


}

#endif
