#ifndef AGILE_ALPGENFHERWIG_HH 
#define AGILE_ALPGENFHERWIG_HH

#include "AGILe/Generator.hh"
#include "AGILe/AlpGen/AlpGen.hh"
#include "AGILe/FHerwig/FHerwig.hh"


namespace AGILe {

  /// Abstract base class for AlpGen interface
  /// @author Jon Butterworth
  /// @author Andy Buckley
  /// @date   2007-10-16
  class AlpGenFHerwig : public FHerwig {
  public:
    /// Standard constructor
    AlpGenFHerwig();
    
    /// Destructor
    ~AlpGenFHerwig() { }

    /// Make sure that generic setParam is visible.
    using Generator::setParam;
  
    /// Pass a parameter to the generator
    bool setParam(const string& name, const string& value);

    /// Generate events	
    void makeEvent(HepMC::GenEvent& evt);


  private:

    // Store an AlpGen interface instance for param passing
    AlpGen _alpgen;
  };
  
}

#endif
