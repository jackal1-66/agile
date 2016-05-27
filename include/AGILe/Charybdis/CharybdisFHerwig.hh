#ifndef AGILE_CHARYBDISFHERWIG_HH 
#define AGILE_CHARYBDISFHERWIG_HH 

#include "AGILe/Generator.hh"
#include "AGILe/Charybdis/Charybdis.hh"
#include "AGILe/FHerwig/FHerwig.hh"

namespace AGILe {


  /// Abstract base class for Charybdis interface
  /// @author Doug Gingrich
  /// @author Andy Buckley
  class CharybdisFHerwig : public FHerwig {
  public:
    /// Standard constructor
    CharybdisFHerwig();
    
    /// Destructor
    ~CharybdisFHerwig() { }

    /// Make sure that generic setParam is visible.
    using FHerwig::setParam;

    /// Pass a parameter to the generator
    bool setParam(const string& name, const string& value);

  private:

    // Store a Charybdis interface instance for param passing
    Charybdis _charybdis;

  };

  
}

#endif
