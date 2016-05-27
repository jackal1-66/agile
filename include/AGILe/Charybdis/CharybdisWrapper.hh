#ifndef AGILE_CHARYBDIS_WRAPPER_HH
#define AGILE_CHARYBDIS_WRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"
#include "HepMC/HEPEVT_Wrapper.h"


/// Charybdis common block declarations.
extern "C" {

  // Les Houches run common block.
  const int MAXPUP=100;
  #define FC_HEPRUP FC_FUNC(heprup, HEPRUP)
  extern struct {
    int IDBMUP[2];
    double EBMUP[2];
    int PDFGUP[2],PDFSUP[2],IDWTUP,NPRUP;
    double XSECUP[MAXPUP],XERRUP[MAXPUP],XMAXUP[MAXPUP];
    int LPRUP[MAXPUP];
  } FC_HEPRUP;

  // Common block for the probabilities of SM particles.
  #define FC_BHPROB FC_FUNC(bhprob, BHPROB)
  extern struct {
    double PQUARK,PLEPT,PNEUT,PGLUON,PGAMMA,PWBOSN,
      PZBOSN,PHIGGS,PFERM[3],PBOSON[5];
  } FC_BHPROB;

  // Common block for the main parameters.
  #define FC_BHPARM FC_FUNC(bhparm, BHPARM)
  extern struct {
    double MPLNCK,MINMSS,MAXMSS,INTMPL;
    int MSSDEF,NBODY,IBHPRN,MSSDEC;
    int TIMVAR,GTSCA,GRYBDY,KINCUT; //Beware, in F77 this is LOGICAL.
  } FC_BHPARM;

  // Common block for decay of the black hole.
  #define FC_BLACKH FC_FUNC(blackh, BLACKH)
  extern struct {
    double RHFACT,BHMASS;
    int TOTDIM;
  } FC_BLACKH;

  // BW mod 16/08/06: new common for version 1.003.
  #define FC_BH1003 FC_FUNC(bh1003, BH1003)
  extern struct {
    double THWMAX,RMMINM;
    int YRCSEC,RMBOIL; //Beware, in F77 this is LOGICAL.
  } FC_BH1003;
}

#endif
