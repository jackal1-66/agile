#ifndef AGILE_FHERWIGWRAPPER_HH
#define AGILE_FHERWIGWRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"
#include "HepMC/IO_HERWIG.h"
#include "HepMC/HEPEVT_Wrapper.h"


extern "C" {

  // Herwig
  #define FC_HWIGIN FC_FUNC(hwigin, HWIGIN)
  void FC_HWIGIN(void);
  #define FC_HWIGUP FC_FUNC(hwigup, HWIGUP)
  void FC_HWIGUP(void);
  #define FC_HWUINC FC_FUNC(hwuinc, HWUINC)
  void FC_HWUINC(void);
  #define FC_HWUSTA FC_FUNC(hwusta, HWUSTA)
  void FC_HWUSTA(const char*, int);
  #define FC_HWEINI FC_FUNC(hweini, HWEINI)
  void FC_HWEINI(void);
  #define FC_HWUINE FC_FUNC(hwuine, HWUINE)
  void FC_HWUINE(void);
  #define FC_HWEPRO FC_FUNC(hwepro, HWEPRO)
  void FC_HWEPRO(void);
  #define FC_HWUPRO FC_FUNC(hwupro, HWUPRO)
  void FC_HWUPRO(void);
  #define FC_HWBGEN FC_FUNC(hwbgen, HWBGEN)
  void FC_HWBGEN(void);
  #define FC_HWDHOB FC_FUNC(hwdhob, HWDHOB)
  void FC_HWDHOB(void);
  #define FC_HWCFOR FC_FUNC(hwcfor, HWCFOR)
  void FC_HWCFOR(void);
  #define FC_HWCDEC FC_FUNC(hwcdec, HWCDEC)
  void FC_HWCDEC(void);
  #define FC_HWDHAD FC_FUNC(hwdhad, HWDHAD)
  void FC_HWDHAD(void);
  #define FC_HWDHVY FC_FUNC(hwdhvy, HWDHVY)
  void FC_HWDHVY(void);
  #define FC_HWMEVT FC_FUNC(hwmevt, HWMEVT)
  void FC_HWMEVT(void);
  #define FC_HWUFNE FC_FUNC(hwufne, HWUFNE)
  void FC_HWUFNE(void);
  #define FC_HWEFIN FC_FUNC(hwefin, HWEFIN)
  void FC_HWEFIN(void);
  #define FC_HWUDPR FC_FUNC(hwudpr, HWUDPR)
  void FC_HWUDPR(void);
  #define FC_HWUEPR FC_FUNC(hwuepr, HWUEPR)
  void FC_HWUEPR(void);
  #define FC_HWUPUP FC_FUNC(hwupup, HWUPUP)
  void FC_HWUPUP(void);
  #define FC_HWUIDT FC_FUNC(hwuidt, HWUIDT)
  void FC_HWUIDT(const int*, int*, int*, char**);

  // Get common block size
  #define FC_HWGETHEPEVTSIZE FC_FUNC(hwgethepevtsize, HWGETHEPEVTSIZE)
  int FC_HWGETHEPEVTSIZE(void);

  // AlpGen matching routine
  #define FC_UPVETO FC_FUNC(upveto, UPVETO)
  void FC_UPVETO(int*);
  
  #define FC_LHEFOPEN FC_FUNC(openlhef, OPENLHEF)
  void FC_LHEFOPEN(const char*, int);

}

void call_lhefopen(const char* file);
#endif
