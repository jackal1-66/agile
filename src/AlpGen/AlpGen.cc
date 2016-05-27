#include "AGILe/AlpGen/AlpGen.hh"
#include "AGILe/AlpGen/AlpGenWrapper.hh"
#include "AGILe/Utils.hh"
// #include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for AlpGen base class
// This is the file-reading interface only. It needs to be used in conjunction
// with FHerwig or FPythia. This class is only to provide access to the parameter
// settings.
//
// Author: Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {


  // Set string parameters
  bool AlpGen::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    // Strings
    if (name == "ALPGENFILE") {
      getLog() << Log::INFO << "Setting ALPGENFILE = " << value << endl;
      size_t nch = (value.size() < 100) ? value.size() : 99;
      for (size_t i = 0; i < 100; i++) {
        if (i < nch) {
          FC_AHIO.FILENAME[i] = value.data()[i];
        } else {
          FC_AHIO.FILENAME[i] = ' ';
        }
      }
    }

    // Integers
    if (name == "IEXC") {
      getLog() << Log::INFO << "Setting ALPGEN IEXC = " << value << endl;
      FC_AHOPTS.IEXC = asInt(value);
    }

    // Doubles
    else if (name == "ETACLMAX") {
      getLog() << Log::INFO << "Setting ETACLMAX = " << value << endl;
      FC_AHOPTS.ETACLMAX = asDouble(value);
    }

    // Fallback
    else {
      //getLog() << Log::ERROR << "AlpGen doesn't have a parameter called " << name << endl;
      return FAILURE;
    }
    return SUCCESS;
  }


}
