// -*- C++ -*-
#ifndef AGILE_FHERWIGJIMMY_HH 
#define AGILE_FHERWIGJIMMY_HH

#include "AGILe/Generator.hh"
#include "AGILe/FHerwig/FHerwig.hh"


namespace AGILe {

  /// Abstract base class for the Fortran-based Herwig generator series
  /// @author Andy Buckley
  /// @date   2007-10-14
  class FHerwigJimmy : public FHerwig {
  public:
    /// Standard constructor
    FHerwigJimmy();
    
    /// Destructor
    ~FHerwigJimmy() { }

    /// Run the generator for one event.
    void makeEvent(HepMC::GenEvent& evt);

    /// Make sure that generic setParam is visible.
    using Generator::setParam;

    /// Pass a parameter to the generator.
    bool setParam(const string& name, const string& value);

    /// Generator name
    virtual const string getName() const{
      return "HerwigJimmy";
    }
    
    /// Tidy up after ourselves
    void finalize();
    
  protected:
    /// Set up default params etc.
    void initialize();
  };
  
}

#endif
  
