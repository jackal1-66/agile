#ifndef AGILE_RAPGAP_HH 
#define AGILE_RAPGAP_HH 

#include "AGILe/Generator.hh"
#include "HepMC/IO_HEPEVT.h"

namespace AGILe {


  /// Abstract base class for Rapgap interface
  /// @author Andy Buckley
  /// @author Holger Schulz
  class Rapgap : public Generator {
  public:
    /// Standard constructor
    Rapgap();
    
    /// Destructor
    virtual ~Rapgap() { }
    
    /// Set up initial state from supplied params
    void setGenSpecificInitialState(PdgCode p1 = PROTON, double e1 = 6000.0, 
                                    PdgCode p2 = PROTON, double e2 = 7000.0);

     /// Make sure that generic setParam is visible.
    using Generator::setParam;

    /// Pass an string parameter to the generator.
    virtual bool setParam(const string& name, const string& value);
       
    /// Generator name
    virtual const string getName() const{
      return "Rapgap";
    }

    /// Run the generator for one event
    void makeEvent(HepMC::GenEvent& evt);


    /// Set the random number generator seed.
    //virtual void setSeed(const int value) {
      //setParam("ISEED", value);
    //}


    //string getPDFSet(PdgCode pid);
    //int getPDFMember(PdgCode pid);
    //string getPDFScheme(PdgCode pid)const;
    
    /// Return the generated cross section in pb.
    virtual const double getCrossSection();
    
    //virtual const string getVersion();
    
    /// Tidy up after ourselves
    void finalize();

  protected:
    /// Set up default params etc.
    void initialize();

    /// Fill a HepMC event
    void fillEvent(HepMC::GenEvent& evt);

    /// Internal storage of initial state params
    string _particleName1, _particleName2;
    double _e1, _e2;

    /// Event counter
    int _nevt;

    /// HEPEVT->HepMC converter
    HepMC::IO_HEPEVT _hepevt;
  };
  

}

#endif
