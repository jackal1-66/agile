#ifndef AGILE_CHARYBDISFHERWIGJIMMY_HH 
#define AGILE_CHARYBDISFHERWIGJIMMY_HH 

#include "AGILe/Generator.hh"
#include "AGILe/Charybdis/Charybdis.hh"
#include "AGILe/FHerwig/FHerwigJimmy.hh"

namespace AGILe {


  /// Abstract base class for Charybdis interface
  /// @author Andy Buckley
  class CharybdisFHerwigJimmy : public FHerwigJimmy {
  public:
    /// Standard constructor
    CharybdisFHerwigJimmy();
    
    /// Destructor
    ~CharybdisFHerwigJimmy() { }

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
