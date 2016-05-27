// -*- C++ -*-
#include "AGILe/Charybdis/CharybdisFPythia.hh"
#include "AGILe/FPythia/FPythia.hh"
#include "AGILe/FPythia/FPythiaWrapper62.hh"
#include "AGILe/Utils.hh"

//-----------------------------------------------------------------------------
// Implementation file for class : CharybdisFPythia
// This is the file-reading interface only. It needs to be used in conjunction
// with FPythia. This class is only to provide access to the parameter
// settings.
//
// Authors: Doug Gingrich
//          Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {


  // Constructor
  CharybdisFPythia::CharybdisFPythia() {
    _myName = "CharybdisPythia";

    FC_HEPRUP.IDBMUP[0] = 2212;
    FC_HEPRUP.IDBMUP[1] = 2212;
    FC_HEPRUP.EBMUP[0] = 7000.0;
    FC_HEPRUP.EBMUP[1] = 7000.0;
    FC_HEPRUP.PDFGUP[0] = -1;
    FC_HEPRUP.PDFGUP[1] = -1;
    FC_HEPRUP.PDFSUP[0] = -1;
    FC_HEPRUP.PDFSUP[1] = -1;
    FC_PYPARS.mstp[142] = 1;
  }


  // Set parameters
  bool CharybdisFPythia::setParam(const string& name, const string& value) {
    // Try Charybdis param handling first
    bool ok = _charybdis.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Herwig param handling
    ok = FPythia::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("CharybdisFPythia doesn't have a parameter called " << name);
    return FAILURE;
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::CharybdisFPythia(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
