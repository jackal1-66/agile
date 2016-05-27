// -*- C++ -*-
#include "AGILe/Cascade/Cascade.hh"
#include "AGILe/Cascade/CascadeWrapper2.hh"
#include "AGILe/Utils.hh"
#include "AGILe/HepMCTools.hh"

#include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for Cascade helper class.
//
// Authors: Doug Gingrich
//          Andy Buckley
//          Holger Schulz
//-----------------------------------------------------------------------------


namespace AGILe {


  // Standard constructor
  Cascade::Cascade() {
    HepMC::HEPEVT_Wrapper::set_max_number_entries(4000);
    HepMC::HEPEVT_Wrapper::set_sizeof_real(8);

    // Start counting events at 1.
    _nevt = 1;
  }

  /// Set up default params etc.
  void Cascade::initialize() {
    Generator::initialize();
    //Cascade::setParam("LEPI", "2212");
    //Cascade::setParam("HADI", "2212");
      //int ISEED = 213123;
      //int N1 = 0;
      //int N2 = 0;
      //call_rm48in(ISEED, N1, N2);

    // Initialise Cascade parameters
    getLog() << Log::INFO << "Initialise Cascade parameters (CASINI)..." << endl;
    call_casini();
    getLog() << Log::INFO << "CASINI is done..." << endl;

    // Read steering file
    getLog() << Log::INFO << "Now calling Steer..." << endl;
    getLog() << Log::INFO << "In case nothing happens from this point on," << endl;
    getLog() << Log::INFO << "make sure you specified a cascade steering file on CL:" << endl;
    getLog() << Log::INFO << "agile-runmc CascadePythia6:423:HEAD < steer_pp ... " << endl;
    call_steer();
    getLog() << Log::INFO << "Steer is done..." << endl;

    // Change standard parameters of Cascade
    getLog() << Log::INFO << "Change standard Cascade parameters (CASCHA)..." << endl;
    call_cascha();
    getLog() << Log::INFO << "CASCHA is done..." << endl;

    // Change standard parameters of Pythia
    getLog() << Log::INFO << "Change standard Pythia parameters (PYTCHA)..." << endl;
    call_pytcha();
    getLog() << Log::INFO << "PYTCHA is done..." << endl;
    //Cascade::setParam("IFPS", 3);

    // Switch on QCD processes by default
    //getLog() << Log::INFO << "Setup basic processes..." << endl;
    //Cascade::setParam("IPRO", 18);
    //Cascade::setParam("IDIR", 0);  // Don't do DIS but diffractive stuff by default
    //Cascade::setParam("INTER", 2);  // Switch to charged current interaction
    ////Cascade::setParam("IDIR", 0);  // Don't do DIS but diffractive stuff by default
    ////Cascade::setParam("NFLAV", 1);  // Set number of flaovurs used in structure functions
    ////Cascade::setParam("NFLQCDC", 1);  // Set number of flaovurs used in structure functions

    // Perform internal Cascade remnant treatment
    Cascade::setParam("ILHA", 0);

    // Set time
    getLog() << Log::INFO << "Calling PTIME..." << endl;
    const char* name = "cascade";
    int j = 1;
    int k = 0;
    call_ptime(name, j, k);

    // Run cascade
    getLog() << Log::INFO << "Now performing basic cross-section integration (CASCADE)..." << endl;
    call_cascade();
    getLog() << Log::INFO << "CASCADE is done..." << endl;

    // Summary of integration result
    call_caend(1);

    _initialized = true;
  }

  void Cascade::setGenSpecificInitialState(PdgCode p1, double e1, PdgCode p2, double e2) {
    getLog() << Log::INFO << "Setting initial state..." << endl;
    Cascade::setParam("KBE1", p1);
    Cascade::setParam("KBE2", p2);
    Cascade::setParam("PBE1", e1);
    Cascade::setParam("PBE2", e2);
  }

  // Run the generator for one event
  void Cascade::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    getLog() << Log::DEBUG << "Fill event Nr: " << _nevt << endl;
    call_event();
    getLog() << Log::DEBUG << "Call pyhepc " << endl;
    call_pyhepc(1);

    // fill the event using HepMC
    Cascade::fillEvent(evt);
    evt.set_event_number(_nevt);
    // Increment an event counter (Cascade does not count for itself (?)).
    _nevt++;
  }

  // Fill a HepMC event
  void Cascade::fillEvent(HepMC::GenEvent& evt) {
    _hepevt.fill_next_event(&evt);
    fixHepMCUnitsFromGeVmm(evt);
    #ifdef HEPMC_HAS_CROSS_SECTION
    const double xsecval = getCrossSection();
    const double xsecerr = FC_CAEFFIC.SD;
    getLog() << Log::DEBUG << "Writing cross-section = " << xsecval << " +- " << xsecerr << endl;
    HepMC::GenCrossSection xsec;
    xsec.set_cross_section(xsecval, xsecerr);
    evt.set_cross_section(xsec);
    #endif
  }

  const double Cascade::getCrossSection(){
    _crossSection = FC_CAEFFIC.AVGI * 1000.0;
    return _crossSection;
  }

  // Set string parameters
  bool Cascade::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    ////// Set double-valued params
    if (name == "PBE1") {
      getLog() << Log::INFO << "Setting ... (PBE1) = " << value << endl;
      FC_CABEAM.PBEAM[0] = -1*asDouble(value);
    }
    else if (name == "PBE2") {
      getLog() << Log::INFO << "Setting ... (PBE2) = " << value << endl;
      FC_CABEAM.PBEAM[1] = asDouble(value);
    }

    //// Set int-valued params
    else if (name == "IFPS") {
      getLog() << Log::INFO << "Setting ... (IFPS) = " << value << endl;
      FC_CAINPU.IFPS = asInt(value);
    }
    else if (name == "ILHA") {
      getLog() << Log::INFO << "Setting ... (ILHA) = " << value << endl;
      FC_CAHERUP.Ilha = asInt(value);
    }
    else if (name == "KBE1") {
      getLog() << Log::INFO << "Setting ... (KBE1) = " << value << endl;
      FC_CABEAM.KBEAM[0] = asInt(value);
    }
    else if (name == "KBE2") {
      getLog() << Log::INFO << "Setting ... (KBE2) = " << value << endl;
      FC_CABEAM.KBEAM[1] = asInt(value);
    }

    else {
      getLog() << Log::ERROR << "Cascade doesn't have a parameter called " << name << endl;
      //return FAILURE;
    }
    return SUCCESS;
  }

  // Tidy up after ourselves
  void Cascade::finalize() {
    getLog() << Log::INFO << "Finalising..." << endl;
    // Print out stats from run
    call_caend(20);
  }

}

extern "C" {
  AGILe::Generator* create() { return new AGILe::Cascade(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
