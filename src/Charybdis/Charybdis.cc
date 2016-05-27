// -*- C++ -*-
#include "AGILe/Charybdis/Charybdis.hh"
#include "AGILe/Charybdis/CharybdisWrapper.hh"
#include "AGILe/Utils.hh"
// #include "HepMC/HEPEVT_Wrapper.h"


//-----------------------------------------------------------------------------
// Implementation file for Charybdis helper class.
// This is a single location for handling of Charybdis parameters between
// several "host" generators cf. the AlpGen class.
//
// Authors: Doug Gingrich
//          Andy Buckley
//-----------------------------------------------------------------------------


namespace AGILe {

  // Set string parameters
  bool Charybdis::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    // Set double-valued params
    if (name == "MPLNCK") {
      MSG_INFO("Setting ... (MPLNCK) = " << value);
      FC_BHPARM.MPLNCK = asDouble(value);
    } else if (name == "MINMSS") {
      MSG_INFO("Setting ... (MINMSS) = " << value);
      FC_BHPARM.MINMSS = asDouble(value);
    } else if (name == "MAXMSS") {
      MSG_INFO("Setting ... (MAXMSS) = " << value);
      FC_BHPARM.MAXMSS = asDouble(value);
    } else if (name == "THWMAX") {
      MSG_INFO("Setting ... (THWMAX) = " << value);
      FC_BH1003.THWMAX = asDouble(value);
    } else if (name == "RMMINM") {
      MSG_INFO("Setting ... (RMMINM) = " << value);
      FC_BH1003.RMMINM = asDouble(value);

    // Set int-valued params
    } else if (name == "PDFGUP") {
      MSG_INFO("Setting Charybdis PDFGUP = " << value);
      FC_HEPRUP.PDFGUP[0] = asInt(value);
      FC_HEPRUP.PDFGUP[1] = asInt(value);
    } else if (name == "PDFSUP") {
      MSG_INFO("Setting Charybdis = " << value);
      FC_HEPRUP.PDFSUP[0] = asInt(value);
      FC_HEPRUP.PDFSUP[1] = asInt(value);
    } else if (name == "MSSDEF") {
      MSG_INFO("Setting ... (MSSDEF) = " << value);
      FC_BHPARM.MSSDEF = asInt(value);
    } else if (name == "NBODY") {
      MSG_INFO("Setting ... (NBODY) = " << value);
      FC_BHPARM.NBODY = asInt(value);
    } else if (name == "IBHPRN") {
      MSG_INFO("Setting ... (IBHPRN) = " << value);
      FC_BHPARM.IBHPRN = asInt(value);
    } else if (name == "MSSDEC") {
      MSG_INFO("Setting ... (MSSDEC) = " << value);
      FC_BHPARM.MSSDEC = asInt(value);
    } else if (name == "TOTDIM") {
      MSG_INFO("Setting ... (TOTDIM) = " << value);
      FC_BLACKH.TOTDIM = asInt(value);

    // Set bool-valued params
    } else if (name == "TIMVAR") {
      MSG_INFO("Setting ... (TIMVAR) = " << value);
      FC_BHPARM.TIMVAR = asInt(value);
    } else if (name == "GTSCA") {
      MSG_INFO("Setting ... (GTSCA) = " << value);
      FC_BHPARM.GTSCA = asInt(value);
    } else if (name == "GRYBDY") {
      MSG_INFO("Setting ... (GRYBDY) = " << value);
      FC_BHPARM.GRYBDY = asInt(value);
    } else if (name == "KINCUT") {
      MSG_INFO("Setting ... (KINCUT) = " << value);
      FC_BHPARM.KINCUT = asInt(value);
    } else if (name == "YRCSEC") {
      MSG_INFO("Setting ... (YRCSEC) = " << value);
      FC_BH1003.YRCSEC = asInt(value);
    } else if (name == "RMBOIL") {
      MSG_INFO("Setting ... (RMBOIL) = " << value);
      FC_BH1003.RMBOIL = asInt(value);
    } else {
      MSG_ERROR("Charybdis doesn't have a parameter called " << name);
      return FAILURE;
    }
    return SUCCESS;
  }


}
