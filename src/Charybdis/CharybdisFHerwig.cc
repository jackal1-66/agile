// -*- C++ -*-
#include "AGILe/Charybdis/CharybdisFHerwig.hh"
#include "AGILe/FHerwig/FHerwig.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/Utils.hh"
//#include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for class : CharybdisFHerwig
// This is the file-reading interface wrapper only. It contains an instance of
// FHerwig which does most of the work. This class is only to provide access to
// the parameter settings.
//
// Authors: Doug Gingrich
//          Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {

  // Standard constructor
  CharybdisFHerwig::CharybdisFHerwig() {
    _myName = "CharybdisHerwig";

    // Set flag to read from LHA event file
    FC_HWPROC.IPROC = -100;
    // PDF defaults
    FC_HEPRUP.PDFGUP[0] = -1;
    FC_HEPRUP.PDFGUP[1] = -1;
    FC_HEPRUP.PDFSUP[0] = -1;
    FC_HEPRUP.PDFSUP[1] = -1;
  }


  // Set string parameters
  bool CharybdisFHerwig::setParam(const string& name, const string& value) {
    // Try Charybdis param handling first
    bool ok = _charybdis.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Herwig param handling
    ok = FHerwig::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("CharybdisFHerwig doesn't have a parameter called " << name);
    return FAILURE;
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::CharybdisFHerwig(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
