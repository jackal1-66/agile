// -*- C++ -*-
#include "AGILe/Rapgap/Rapgap.hh"
#include "AGILe/Rapgap/RapgapWrapper32.hh"
//#include "AGILe/FPythia/FPythia.hh"
#include "AGILe/FPythia/FPythiaWrapper.hh"
#include "AGILe/Utils.hh"
#include "AGILe/HepMCTools.hh"

#include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for Rapgap helper class.
//
// Authors: Doug Gingrich
//          Andy Buckley
//          Holger Schulz
//-----------------------------------------------------------------------------


namespace AGILe {


  // Standard constructor
  Rapgap::Rapgap() {
    HepMC::HEPEVT_Wrapper::set_sizeof_real(8);

    _particleNames[ELECTRON]    = "e-";
    _particleNames[POSITRON]    = "e+";
    _particleNames[PROTON]      = "p+";
    _particleNames[ANTIPROTON]  = "pbar-";
    _particleNames[NEUTRON]     = "n0";
    _particleNames[ANTINEUTRON] = "nbar0";
    _particleNames[PHOTON]      = "gamma";
    _particleNames[MUON]        = "mu-";
    _particleNames[ANTIMUON]    = "mu+";
    // TAU, ANTITAU
    _particleNames[NU_E]        = "nu_e";
    _particleNames[NU_EBAR]     = "nu_ebar";
    _particleNames[NU_MU]       = "nu_mu";
    _particleNames[NU_MUBAR]    = "nu_mubar";
    _particleNames[NU_TAU]      = "nu_tau";
    _particleNames[NU_TAUBAR]   = "nu_taubar";
    _particleNames[PIPLUS]      = "pi+";
    _particleNames[PIMINUS]     = "pi-";

    // Start counting events at 1.
    _nevt = 1;
  }

  /// Set up default params etc.
  void Rapgap::initialize() {
    Generator::initialize();
    //Rapgap::setParam("LEPI", "2212");
    //Rapgap::setParam("HADI", "2212");
      //int ISEED = 213123;
      //int N1 = 0;
      //int N2 = 0;
      //call_rm48in(ISEED, N1, N2);
    //call_rapgap();
    // Initialise Rapgap parameters
    getLog() << Log::INFO << "Now calling GRAINI..." << endl;
    call_graini();
    getLog() << Log::INFO << "GRAINI is done..." << endl;

    // Switch on QCD processes by default
    getLog() << Log::INFO << "Setup basic processes..." << endl;
    //Rapgap::setParam("IPRO", 18);
    //Rapgap::setParam("IDIR", 0);  // Don't do DIS but diffractive stuff by default
    //Rapgap::setParam("INTER", 2);  // Switch to charged current interaction
    ////Rapgap::setParam("IDIR", 0);  // Don't do DIS but diffractive stuff by default
    ////Rapgap::setParam("NFLAV", 1);  // Set number of flaovurs used in structure functions
    ////Rapgap::setParam("NFLQCDC", 1);  // Set number of flaovurs used in structure functions

    getLog() << Log::INFO << "Now calling Steer..." << endl;
    getLog() << Log::INFO << "In case nothing happens from this point on," << endl;
    getLog() << Log::INFO << "make sure you specified a cascade steering file on CL:" << endl;
    getLog() << Log::INFO << "agile-runmc RapgapPythia6:X:Y < steer_pp ... " << endl;
    call_steer();
    //getLog() << Log::INFO << "Steer is done..." << endl;

    getLog() << Log::INFO << "Change standard RAPGAP parameters..." << endl;
    call_rapcha();
    //getLog() << Log::INFO << "Change standard HERACLES parameters..." << endl;
    call_hercha();
    //getLog() << Log::INFO << "Change standard PYTHIA parameters..." << endl;
    call_pytcha();

    //getLog() << Log::INFO << "Change standard ARIADNE parameters..." << endl;
    //call_aricha();
    //getLog() << Log::INFO << "Init ARIADNE..." << endl;
    //const char* NAME = "RAPGAP";
    //call_arinit(NAME);

    getLog() << Log::INFO << "Calling PTIME..." << endl;
    const char* name = "rapgap";
    int j = 1;
    int k = 0;
    call_ptime(name, j, k);

    getLog() << Log::INFO << "Now perfroming basic cross-section integration..." << endl;
    call_rapgap();
    getLog() << Log::INFO << "RAPGAP is done..." << endl;
    call_raend(1);
    _initialized = true;
  }

  void Rapgap::setGenSpecificInitialState(PdgCode p1, double e1, PdgCode p2, double e2) {
    getLog() << Log::INFO << "Setting initial state..." << endl;
    // For Pythia, we have to hold on to this state until initialize() is called.
    //_particleName1 = _particleNames[p1];
    //_particleName2 = _particleNames[p2];
    /// @todo Get momenta and energies unconfused.
    //Rapgap::setParam("KBE1", _particleNames[ParticleName(p1)]);
    //Rapgap::setParam("KBE2", _particleNames[ParticleName(p2)]);
    Rapgap::setParam("KBE1", p1);
    Rapgap::setParam("KBE2", p2);
    Rapgap::setParam("PBE1", e1);
    Rapgap::setParam("PBE2", e2);
    //Rapgap::setParam("PLEP", e1);
    //Rapgap::setParam("PPIN", e2);
    //Rapgap::setParam("LEPI", p1);
    //Rapgap::setParam("HADI", p2);
  }

  // Run the generator for one event
  void Rapgap::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    call_event();
    call_pyhepc(1);
    // fill the event using HepMC
    Rapgap::fillEvent(evt);
    evt.set_event_number(_nevt);
    // Increment an event counter (Pythia does not count for itself).
    _nevt++;
  }

  // Fill a HepMC event
  void Rapgap::fillEvent(HepMC::GenEvent& evt) {
    _hepevt.fill_next_event(&evt);
    fixHepMCUnitsFromGeVmm(evt);
    #ifdef HEPMC_HAS_CROSS_SECTION
    const double xsecval = getCrossSection();
    const double xsecerr = FC_EFFIC.SD;
    getLog() << Log::DEBUG << "Writing cross-section = " << xsecval << " +- " << xsecerr << endl;
    HepMC::GenCrossSection xsec;
    xsec.set_cross_section(xsecval, xsecerr);
    evt.set_cross_section(xsec);
    #endif
  }

  const double Rapgap::getCrossSection(){
    _crossSection = FC_EFFIC.AVGI * 1000.0;
    return _crossSection;
  }

  // Set string parameters
  bool Rapgap::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    //// Set double-valued params
    if (name == "PPIN") {
      getLog() << Log::INFO << "Setting ... (PPIN) = " << value << endl;
      FC_INPU.PIN = -1*asDouble(value);
    } else if (name == "PLEP") {
      getLog() << Log::INFO << "Setting ... (PLEP) = " << value << endl;
      FC_INPU.PLEPIN = asDouble(value);
    }
    else if (name == "PBE1") {
      getLog() << Log::INFO << "Setting ... (PBE1) = " << value << endl;
      //FC_BEAM.PBEAM[0] = -1*asDouble(value);
      FC_BEAM.PBE1 = -1*asDouble(value);
    }
    else if (name == "PBE2") {
      getLog() << Log::INFO << "Setting ... (PBE2) = " << value << endl;
      FC_BEAM.PBEAM[1] = asDouble(value);
    }
    else if (name == "PT2CUT") {
      getLog() << Log::INFO << "Setting ... (PT2CUT) = " << value << endl;
      FC_PTCUT.PT2CUT[1] = asDouble(value);
    }

    //// Set int-valued params
    else if (name == "KBE1") {
      getLog() << Log::INFO << "Setting ... (KBE1) = " << value << endl;
      FC_BEAM.KBEAM[0] = -1*asInt(value);
    }
    else if (name == "KBE2") {
      getLog() << Log::INFO << "Setting ... (KBE2) = " << value << endl;
      FC_BEAM.KBEAM[1] = asInt(value);
    }
    else if (name == "HADI") {
      getLog() << Log::INFO << "Setting ... (HADI) = " << value << endl;
      FC_INPU.HADI = asInt(value);
    } else if (name == "LEPI") {
      getLog() << Log::INFO << "Setting ... (LEPI) = " << value << endl;
      FC_INPU.LEPI = asInt(value);
    } else if (name == "IPRO") {
      getLog() << Log::INFO << "Setting ... (IPRO) = " << value << endl;
      FC_RAPA.IPRO = asInt(value);
    } else if (name == "IDIR") {
      getLog() << Log::INFO << "Setting ... (IDIR) = " << value << endl;
      FC_DISDIF.IDIR = asInt(value);
    } else if (name == "NFLAV") {
      getLog() << Log::INFO << "Setting ... (NFLAV) = " << value << endl;
      FC_LUCO.NFLAV = asInt(value);
    } else if (name == "NFLQCDC") {
      getLog() << Log::INFO << "Setting ... (NFLQCDC) = " << value << endl;
      FC_LUCO.NFLQCDC = asInt(value);
    } else if (name == "INTER") {
      getLog() << Log::INFO << "Setting ... (INTER) = " << value << endl;
      FC_INPU.INTER = asInt(value);
    }

    else {
      getLog() << Log::ERROR << "Rapgap doesn't have a parameter called " << name << endl;
      //return FAILURE;
    }
    return SUCCESS;
  }

  // Tidy up after ourselves
  void Rapgap::finalize() {
    getLog() << Log::INFO << "Finalising..." << endl;
    // Print out stats from run
    call_raend(20);
  }

}

extern "C" {
  AGILe::Generator* create() { return new AGILe::Rapgap(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
