// -*- C++ -*-
#include "AGILe/AlpGen/AlpGenFHerwig.hh"
#include "AGILe/AlpGen/AlpGenWrapper.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/Utils.hh"
#include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for class : AlpGenFHerwig
// This is the file-reading interface wrapper only. It contains an instance of
// FHerwig which does most of the work. This class is only to provide access to
// the parameter
// settings.
//
// Authors: Jon Butterworth
//          Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {


  // Standard constructor
  AlpGenFHerwig::AlpGenFHerwig() {
    _myName = "AlpGenHerwig";

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
  bool AlpGenFHerwig::setParam(const string& name, const string& value) {
    // Try AlpGen param handling first
    bool ok = _alpgen.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Herwig param handling
    ok = FHerwig::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("AlpGenHerwig doesn't have a parameter called " << name);
    return FAILURE;
  }


  // Call event generation with veto routine for MLM matching
  void AlpGenFHerwig::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    while (true) {
      FC_HWUINE();  // Initialize event
      FC_HWEPRO();  // Generate hard subprocess
      // Call the matching routine
      int imatch = 0;
      FC_UPVETO(&imatch);
      if (imatch != 0) {
        MSG_DEBUG("Event killed by UPVETO");
        FC_HWEVNT.IERROR = -1;
        FC_HWUFNE();
        continue;
      }
      break;
    }
    FC_HWBGEN();  // Generate parton cascade
    FC_HWDHOB();  // Do heavy quark decays
    if (_doHadronise) {
      FC_HWCFOR();  // Do cluster formation
      FC_HWCDEC();  // Do cluster decays
      FC_HWDHAD();  // Do unstable particle decays
      FC_HWDHVY();  // Do heavy flavor decays
      FC_HWMEVT();  // Add soft underlying event
    }
    FC_HWUFNE();  // Finish event
    fillEvent(evt);
    return;
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::AlpGenFHerwig(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
