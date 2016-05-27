// -*- C++ -*-
#include "AGILe/AlpGen/AlpGenFHerwigJimmy.hh"
#include "AGILe/AlpGen/AlpGenWrapper.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/FHerwig/JimmyWrapper.hh"
#include "AGILe/Utils.hh"
#include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for class : AlpGenFHerwigJimmy
// This is the file-reading interface wrapper only. It contains an instance of
// FHerwigJimmy which does most of the work. This class is only to provide access to
// the parameter
// settings.
//
// Authors: Jon Butterworth
//          Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {


  // Standard constructor
  AlpGenFHerwigJimmy::AlpGenFHerwigJimmy() {
    // Set flag to read from LHA event file
    FC_HWPROC.IPROC = -100;
    _iprocset = true;

    // Set the ALPGEN filename to "zhjj" by default
    FC_AHIO.FILENAME[0] = 'z';
    FC_AHIO.FILENAME[1] = 'h';
    FC_AHIO.FILENAME[2] = 'j';
    FC_AHIO.FILENAME[3] = 'j';
  }


  // Set string parameters
  bool AlpGenFHerwigJimmy::setParam(const string& name, const string& value) {
    // Try AlpGen param handling first
    bool ok = _alpgen.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Herwig+Jimmy param handling
    ok = FHerwigJimmy::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("AlpGenHerwigJimmy doesn't have a parameter called " << name);
    return FAILURE;
  }


  // Call event generation with veto routine for MLM matching
  void AlpGenFHerwigJimmy::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    while (true) {
      int counter(0);
      // Repeat the first stages of event generation until multiple
      // scattering succeeds (or isn't run at all).
      while (true) {
        FC_HWUINE();  // Initialize event
        FC_HWEPRO();  // Generate hard subprocess

        // Call the AlpGen matching routine
        int imatch = 0;
        FC_UPVETO(&imatch);
        if (imatch != 0) {
          MSG_DEBUG("Event killed by UPVETO");
          FC_HWEVNT.IERROR = -1;
          FC_HWUFNE();
          continue;
        }

        counter += 1;

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


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::AlpGenFHerwigJimmy(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
