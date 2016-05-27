#ifndef AGILE_ALPGEN_WRAPPER_HH
#define AGILE_ALPGEN_WRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"


/// Alpgen common block declarations
extern "C" {

  // common/AHio/Nunit,NunitOut,NunitIni,filename
  #define FC_AHIO FC_FUNC(ahio, AHIO)
  extern struct {
    int NUNIT,NUNITOUT,NUNITINI;
    char FILENAME[100];
  } FC_AHIO;

  // Inputs for the matching algorithm:
  //   integer iexc,npfst,nplst,nljets,njstart,njlast,ickkw
  //   double precision etclus,rclus,etaclmax
  //   common/AHopts/etclus,rclus,etaclmax,iexc,npfst,nplst,nljets,njstart,njlast,ickkw
  #define FC_AHOPTS FC_FUNC(ahopts, AHIO)
  extern struct {
    double ETCLUS,RCLUS,ETACLMAX;
    int IEXC,NPFST,NPLST,NLJETS,NJSTART,NJLAST,ICKKW;
  } FC_AHOPTS;

}

#endif
