#ifndef AGILE_ALPGENFHERWIGJIMMY_HH 
#define AGILE_ALPGENFHERWIGJIMMY_HH

#include "AGILe/Generator.hh"
#include "AGILe/AlpGen/AlpGen.hh"
#include "AGILe/FHerwig/FHerwigJimmy.hh"

namespace AGILe {


  /// Abstract base class for AlpGen + Herwig + Jimmy interface
  /// @author Andy Buckley
  /// @date   2009-06-30
  class AlpGenFHerwigJimmy : public FHerwigJimmy {
  public:
    /// Standard constructor
    AlpGenFHerwigJimmy();
    
    /// Destructor
    ~AlpGenFHerwigJimmy() { }

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
