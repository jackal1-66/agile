#ifndef AGILE_ALPGENFPYTHIA_HH
#define AGILE_ALPGENFPYTHIA_HH

#include "AGILe/Generator.hh"
#include "AGILe/AlpGen/AlpGen.hh"
#include "AGILe/FPythia/FPythia.hh"

namespace AGILe {


  /// Abstract base class for AlpGen interface
  /// @author Jon Butterworth
  /// @author Andy Buckley
  class AlpGenFPythia : public FPythia {
  public:
    /// Standard constructor.
    AlpGenFPythia();

    /// Destructor.
    ~AlpGenFPythia() { }

    /// Make sure that generic setParam is visible.
    using Generator::setParam;

    /// Pass a parameter to the generator.
    bool setParam(const string& name, const string& value);


  private:

    // Store an AlpGen interface instance for param passing
    AlpGen _alpgen;

  };


}

#endif
