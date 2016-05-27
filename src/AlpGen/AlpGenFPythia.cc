#include "AGILe/AlpGen/AlpGenFPythia.hh"
#include "AGILe/AlpGen/AlpGenWrapper.hh"
#include "AGILe/Utils.hh"
#include "HepMC/HEPEVT_Wrapper.h"

namespace AGILe {


  // Standard constructor
  AlpGenFPythia::AlpGenFPythia() {
    _myName = "AlpGenPythia";

    // Set flag to read from LHA event file
    FPythia::setParam("MSTP(143)", 1);

    // Set the ALPGEN filename to "zhjj" by default
    FC_AHIO.FILENAME[0] = 'z';
    FC_AHIO.FILENAME[1] = 'h';
    FC_AHIO.FILENAME[2] = 'j';
    FC_AHIO.FILENAME[3] = 'j';
  }


  // Set string parameters
  bool AlpGenFPythia::setParam(const string& name, const string& value) {
    // Try AlpGen param handling first
    bool ok = _alpgen.setParam(name, value);
    if (ok) return SUCCESS;
    // Fall back to Pythia param handling
    ok = FPythia::setParam(name, value);
    if (ok) return SUCCESS;
    // Fail
    MSG_ERROR("AlpGenPythia doesn't have a parameter called " << name);
    return FAILURE;
  }


  /// @todo No need for an explicit vetoing routine?

}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::AlpGenFPythia(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
