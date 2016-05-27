#ifndef AGILE_JIMMY_WRAPPER_HH
#define AGILE_JIMMY_WRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"


extern "C" {

  // Jimmy
  #define FC_JMINIT FC_FUNC(jminit, JMINIT)
  void FC_JMINIT(void);
  #define FC_JIMMIN FC_FUNC(jimmin, JIMMIN)
  void FC_JIMMIN(void);
  #define FC_HWMSCT FC_FUNC(hwmsct, HWMSCT)
  void FC_HWMSCT(int*);
  #define FC_JMEFIN FC_FUNC(jmefin, JMEFIN)
  void FC_JMEFIN(void);

  //      COMMON / JMPARM /  PTJIM, YGAMMA, JMZMIN, JMRAD(264)
  //     &     ,PHAD, JMU2, JMV2, JMARRY( 6+MAXMS,0:NPSIMP )
  //     &     ,NLOST, TOTSCAT, ANOMOFF, JCMVAR, JMUEO
  //     &     ,JMPTYP(NPROC), JMBUG, FN_TYPE, MSFLAG, MAXMSTRY
  const int npsimp = 16;
  const int maxms = 100;
  const int nproc = 117;
  #define FC_JMPARM FC_FUNC(jmparm, JMPARM)
  extern struct {
    double PTJIM,YGAMMA,JMZMIN,JMRAD[264],PHAD,JMU2,JMV2,JMARRY[npsimp+1][6+maxms];
    double NLOST, TOTSCAT; 
    int ANOMOFF, JCMVAR, JMUEO, JMPTYP[nproc], JMBUG, FN_TYPE;
    int MSFLAG, MAXMSTRY;
    // ANOMOFF is F77 logical.
  } FC_JMPARM;


}

#endif
