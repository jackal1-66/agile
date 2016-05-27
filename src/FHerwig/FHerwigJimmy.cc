// -*- C++ -*-
#include "AGILe/FHerwig/FHerwigJimmy.hh"
#include "AGILe/FHerwig/FHerwig.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/FHerwig/JimmyWrapper.hh"
#include "AGILe/Utils.hh"


namespace AGILe {

  // Standard constructor
  FHerwigJimmy::FHerwigJimmy() {
    _myName = "HerwigJimmy";

    // NB. FHerwig constructor gets automatically called first.
    FC_JMPARM.JMBUG = 0;
    // Initialise Jimmy common blocks.
    FC_JIMMIN();
  }


  // Run generator initialization
  void FHerwigJimmy::initialize() {
    FHerwig::initialize();

    // Initialise Jimmy.
    if (FC_JMPARM.MSFLAG == 1) {
      FC_JMINIT();
    }

    _initialized = true;
  }


  // Set parameters.
  bool FHerwigJimmy::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    // Integers.
    if (name == "JMUEO") {
      MSG_INFO("Setting JMUEO = " << asInt(value));
      FC_JMPARM.JMUEO = asInt(value);
    } else if (name == "JMBUG") {
      MSG_INFO("Setting JMBUG = " << asInt(value));
      FC_JMPARM.JMBUG = asInt(value);
    } else if (name == "MSFLAG") {
      MSG_INFO("Setting MSFLAG = " << asInt(value));
      FC_JMPARM.MSFLAG = asInt(value);
    }

    // Doubles.
    else if (name == "PTJIM") {
      MSG_INFO("Setting minimum PT for secondary scatters (PTJIM) = " << asDouble(value));
      FC_JMPARM.PTJIM = asDouble(value);
    } else if (name == "PHAD") {
      MSG_INFO("Setting hadronic photon inverse probability (PHAD) = " << asDouble(value));
      FC_JMPARM.PHAD = asDouble(value);
    } else if (name == "PRRAD") {
      MSG_INFO("Setting 1/(Proton radius)2 (PRRAD) = " << asDouble(value));
      FC_JMPARM.JMRAD[72] = asDouble(value);
      FC_JMPARM.JMRAD[74] = asDouble(value);
      FC_JMPARM.JMRAD[90] = asDouble(value);
      FC_JMPARM.JMRAD[92] = asDouble(value);
    } else if (name == "PHRAD") {
      MSG_INFO("Setting 1/(Photon radius)2 (PRRAD) = " << asDouble(value));
      FC_JMPARM.JMRAD[58]  = asDouble(value);
      FC_JMPARM.JMRAD[120] = asDouble(value);
      FC_JMPARM.JMRAD[126] = asDouble(value);
    }

    // Boolean (as int).
    else if (name == "ANOMOFF") {
      MSG_INFO("Setting MI in anomalous photon events (ANOMOFF) = " << asInt(value));
      FC_JMPARM.ANOMOFF = asInt(value);
    }

    // Fall back to FHerwig.
    else if (FHerwig::setParam(name, value) != SUCCESS) {
      MSG_ERROR(getName() << " doesn't have a parameter called " << name);
      return FAILURE;
    }
    return SUCCESS;
  }


  // Run the generator for one event
  /// @todo Make sub-process execution conditional.
  void FHerwigJimmy::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    while (true) {
      int counter(0);
      // Repeat the first stages of event generation until multiple
      // scattering succeeds (or isn't run at all).
      while (true) {
        counter += 1;

        FC_HWUINE();  // Initialize event
        FC_HWEPRO();  // Generate hard subprocess
        FC_HWBGEN();  // Generate parton cascade

        // Call the multiple scattering routine with the abort flag.
        // If abort is returned with value 1 (true), then abandon the
        // event. This implementation makes sure that the event generation
        // continues if multiple scattering is disabled (MSFLAG != 1)
        int abort(0);
        if (FC_JMPARM.MSFLAG == 1) FC_HWMSCT(&abort);
        // If MS is okay or disabled, escape the loop and
        // continue with the decays and hadronisation.
        if (abort == 0) {
          MSG_DEBUG("Num attempts to make MPI = " << counter);
          break;
        }

        // Check for too many attempts to make MPI scatters
        if (counter > 100) {
          throw runtime_error("Too many attempts to make MPI in FHerwigJimmy");
        }
      }
      FC_HWDHOB();  // Do heavy quark decays
      if (_doHadronise) {
        FC_HWCFOR();  // Do cluster formation
        FC_HWCDEC();  // Do cluster decays
        FC_HWDHAD();  // Do unstable particle decays
        FC_HWDHVY();  // Do heavy flavor decays
        FC_HWMEVT();  // Add soft underlying event
      }
      FC_HWUFNE();  // Finish event
      if (FC_HWEVNT.IERROR == 0) break;
    }
    clearEvent(evt);
    fillEvent(evt);
  }


  /// Tidy up, print out run stats, etc.
  void FHerwigJimmy::finalize() {
    FHerwig::finalize();
    if (FC_JMPARM.MSFLAG == 1) {
      FC_JMEFIN();
    }
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::FHerwigJimmy(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
