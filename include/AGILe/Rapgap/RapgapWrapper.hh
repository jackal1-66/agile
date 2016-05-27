#ifndef AGILE_RAPGAP_WRAPPER_HH
#define AGILE_RAPGAP_WRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"


extern "C" {
  #define FC_GRAINI FC_FUNC(graini, GRAINI)
  void FC_GRAINI();
  #define FC_Steer FC_FUNC(steer, Steer)
  void FC_Steer();
  #define FC_RAPGAP FC_FUNC(rapgap, RAPGAP)
  void FC_RAPGAP();
  #define FC_rapcha FC_FUNC(rapcha, rapcha)
  void FC_rapcha();
  #define FC_HERCHA FC_FUNC(hercha, HERCHA)
  void FC_HERCHA();
  #define FC_PYTCHA FC_FUNC(pytcha, PYTCHA)
  void FC_PYTCHA();
  #define FC_ARICHA FC_FUNC(aricha, ARICHA)
  void FC_ARICHA();
  #define FC_ARINIT FC_FUNC(arinit, ARINIT)
  void FC_ARINIT(const char *);
  #define FC_RAEND FC_FUNC(raend, RAEND)
  void FC_RAEND(int *);
  #define FC_EVENT FC_FUNC(event, EVENT)
  void FC_EVENT();
  #define FC_PTIME FC_FUNC(ptime, PTIME)
  void FC_PTIME(const char *, int* , int* );
  // Pythia  routines
  #define FC_PYHEPC FC_FUNC(pyhepc, PYHEPC)
  void FC_PYHEPC(int*);
  //#define FC_RM48IN FC_FUNC(rm48in, RM48IN)
  //void FC_RM48IN(int ISEED, int N1, int N2);
  
  
}

void call_graini();
void call_ptime(const char * name, int j, int k);
void call_steer();
void call_rapgap();
void call_rapcha();
void call_hercha();
void call_pytcha();
void call_aricha();
void call_arinit(const char * name);

// A pythia routine
void call_pyhepc(int mode);

void call_raend(int i);
void call_event();
// This is for setting the random seed
//void call_rm48in(int ISEED, int N1, int N2);
#endif
