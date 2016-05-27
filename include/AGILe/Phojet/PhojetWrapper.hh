#ifndef AGILE_FPHOJETWRAPPER_HH
#define AGILE_FPHOJETWRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"

extern "C" {
  #define FC_PYHEPC FC_FUNC(pyhepc, PYHEPC)
  void FC_PYHEPC(int*);
  #define FC_PYINIT FC_FUNC(pyinit, PYINIT)
  void FC_PYINIT(const char*,const char*,const char*,double*,int,int,int);
  #define FC_PYGIVE FC_FUNC(pygive, PYGIVE)
  void FC_PYGIVE(const char*,int);
  #define FC_PYLIST FC_FUNC(pylist, PYLIST)
  void FC_PYLIST(int*);
  #define FC_PYSTAT FC_FUNC(pystat, PYSTAT)
  void FC_PYSTAT(int*);
  #define FC_PYEVNT FC_FUNC(pyevnt, PYEVNT)
  void FC_PYEVNT();
  #define FC_UPINIT FC_FUNC(upinit, UPINIT)
  void FC_UPINIT();
  #define FC_UPEVNT FC_FUNC(upevnt, UPENVT)
  void FC_UPEVNT();
  #define FC_INITPYDATA FC_FUNC(initpydata, INITPYDATA)
  void FC_INITPYDATA();
  #define FC_PHO_SETPAR FC_FUNC(pho_setpar, PHO_SETPAR)
  void FC_PHO_SETPAR(int*,int*,int*,double*);
  #define FC_PHO_INIT FC_FUNC(pho_init, PHO_INIT)
  void FC_PHO_INIT(int*,int*);
  #define FC_PHO_EVENT FC_FUNC(pho_event, PHO_EVENT)
  void FC_PHO_EVENT(int*,double*,double*,double*,int*);
  #define FC_PHO_HEPEVT FC_FUNC(pho_hepevt, PHO_HEPEVT)
  void FC_PHO_HEPEVT();
  #define FC_PHO_RNDIN FC_FUNC(pho_rndin, PHO_RNDIN)
  void FC_PHO_RNDIN(int*,int*,int*,int*);
}

// Define methods to hide the subtle syntax necessary to call Fortran from C++
void call_pyhepc(int mode);
void call_pyinit(const char* frame, const char* beam, const char* target, double win); 
void call_pygive(const char* frame ); 
void call_pylist(int mode);
void call_pystat(int mode);
void call_pyevnt();
void call_pho_setpar(int i,int id ,int mode ,double val);
void call_pho_init(int mode ,int irej);
void call_pho_event(int mode, double p1, double p2, double sig, int irej);
void call_pho_hepevt();
void call_pho_rndin(int rndm1,int rndm2,int rndm3, int rndm4);
#endif
