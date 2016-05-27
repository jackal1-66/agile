// -*- C++ -*-
#ifndef AGILE_FHERWIG_HH
#define AGILE_FHERWIG_HH

#include "AGILe/Generator.hh"

namespace AGILe {

  /// Abstract base class for the Fortran-based Herwig generator series
  /// @author Andy Buckley
  class FHerwig : public Generator {
  public:
    /// Standard constructor
    FHerwig();

    /// Destructor
    virtual ~FHerwig() {}

    /// Set up initial state from supplied params.
    virtual void setGenSpecificInitialState(PdgCode p1 = PROTON, double e1 = 7000.0,
                                            PdgCode p2 = PROTON, double e2 = 7000.0);

    /// Run the generator for one event.
    virtual void makeEvent(HepMC::GenEvent& evt);

    /// Set the random number generator seed.
    virtual void setSeed(const int value);

    /// Make sure that generic setParam is visible.
    using Generator::setParam;

    /// Pass a parameter to the generator.
    virtual bool setParam(const string& name, const string& value);

    /// Tidy up after ourselves
    virtual void finalize();

    string getPDFSet(PdgCode pid);
    int getPDFMember(PdgCode pid);
    string getPDFScheme(PdgCode pid)const;

    const virtual double getCrossSection();


  protected:

    /// Set up default params etc.
    virtual void initialize();

    /// Fill a HepMC event
    virtual void fillEvent(HepMC::GenEvent& evt);

    /// Flag to determine if the hadronisation process will be run.
    bool _doHadronise;

    /// Flag to determine if weighted or unweighted events are to be generated.
    bool _unitWeight;

    /// Flag to determine if the process code has been set.
    bool _iprocset;


  private:

    /// @brief Get a beam particle code for a given PID code.
    /// Return the beam number (0 or 1) of a particle.
    /// Return -1 if not a beam particle
    int _beamNumber(PdgCode pid);

    /// @brief Process store parameters
    /// HWIGIN needs IPROC to be set before being called, AND when called it will
    /// overwrite all other common block values! So we need to store the params
    /// provided by the user (other than IPROC) and then apply all these en-masse
    /// in the @c initialize() method, just after HWIGIN has been called. *sigh*
    bool _processParams();

    /// @brief Map of params and values used by @c _processParams
    map<string,string> _storedParams;

    /// Event counter
    int _nevt;

  };

}

#endif
