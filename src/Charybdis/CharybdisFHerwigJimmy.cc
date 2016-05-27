// -*- C++ -*-
#include "AGILe/Charybdis/CharybdisFHerwigJimmy.hh"
#include "AGILe/FHerwig/FHerwigJimmy.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/Utils.hh"
//#include "HepMC/HEPEVT_Wrapper.h"

//-----------------------------------------------------------------------------
// Implementation file for class : CharybdisFHerwigJimmy
//
// This is the file-reading interface wrapper only. It uses the FHerwigJimmy and
// Charybdis classes to do most of the work. This class is only to provide
// access to the parameter settings.
//
// Authors: Doug Gingrich
//          Andy Buckley
//-----------------------------------------------------------------------------

namespace AGILe {


  // Standard constructor
  CharybdisFHerwigJimmy::CharybdisFHerwigJimmy() {
    _myName = "CharybdisHerwigJimmy";

    // Set flag to read from LHA event file
    FC_HWPROC.IPROC = -100;
    // PDF defaults
    FC_HEPRUP.PDFGUP[0] = -1;
    FC_HEPRUP.PDFGUP[1] = -1;
    FC_HEPRUP.PDFSUP[0] = -1;
    FC_HEPRUP.PDFSUP[1] = -1;
  }


  // Set string parameters
  bool CharybdisFHerwigJimmy::setParam(const string& name, const string& value) {
    // Try Charybdis param handling first
    bool ok = _charybdis.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Herwig+Jimmy param handling
    ok = FHerwigJimmy::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("CharybdisHerwigJimmy doesn't have a parameter called " << name);
    return FAILURE;
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::CharybdisFHerwigJimmy(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
