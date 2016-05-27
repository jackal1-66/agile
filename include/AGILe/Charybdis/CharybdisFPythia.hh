#ifndef AGILE_CHARYBDISFPYTHIA_HH
#define AGILE_CHARYBDISFPYTHIA_HH

#include "AGILe/Generator.hh"
#include "AGILe/Charybdis/Charybdis.hh"
#include "AGILe/FPythia/FPythia.hh"

namespace AGILe {


  /// Abstract base class for Charybdis interface
  /// @author Doug Gingrich
  /// @author Andy Buckley
  class CharybdisFPythia : public FPythia {
  public:
    /// Standard constructor.
    CharybdisFPythia();

    /// Destructor.
    ~CharybdisFPythia() { }

    /// Make sure that generic setParam is visible.
    using Generator::setParam;

    /// Pass a parameter to the generator.
    bool setParam(const string& name, const string& value);


  private:

    // Store a Charybdis interface instance for param passing
    Charybdis _charybdis;

  };


}

#endif
