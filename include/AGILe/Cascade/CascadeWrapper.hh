#ifndef AGILE_CASCADE_WRAPPER_HH
#define AGILE_CASCADE_WRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"



extern "C" {
  #define FC_CASINI FC_FUNC(casini, CASINI)
  void FC_CASINI();
  #define FC_Steer FC_FUNC(steer, Steer)
  void FC_Steer();
  #define FC_CASCADE FC_FUNC(cascade, CASCADE)
  void FC_CASCADE();
  #define FC_CASCHA FC_FUNC(cascha, CASCHA)
  void FC_CASCHA();
  #define FC_PYTCHA FC_FUNC(pytcha, PYTCHA)
  void FC_PYTCHA();
  #define FC_ARICHA FC_FUNC(aricha, ARICHA)
  void FC_ARICHA();
  #define FC_ARINIT FC_FUNC(arinit, ARINIT)
  void FC_ARINIT(const char *);
  #define FC_CAEND FC_FUNC(caend, CAEND)
  void FC_CAEND(int *);
  #define FC_EVENT FC_FUNC(event, EVENT)
  void FC_EVENT();
  #define FC_CAUPEVNT FC_FUNC(caupevnt, CAUPEVNT)
  void FC_CAUPEVNT();
  #define FC_PTIME FC_FUNC(ptime, PTIME)
  void FC_PTIME(const char *, int* , int* );
  // Pythia  routines
  #define FC_PYHEPC FC_FUNC(pyhepc, PYHEPC)
  void FC_PYHEPC(int*);
  //#define FC_RM48IN FC_FUNC(rm48in, RM48IN)
  //void FC_RM48IN(int ISEED, int N1, int N2);
  
  #define FC_PYINIT FC_FUNC(pyinit, PYINIT)
  void FC_PYINIT(const char*,const char*,const char*,double*,int,int,int);
  #define FC_PYGIVE FC_FUNC(pygive, PYGIVE)
  void FC_PYGIVE(const char*,int);
  #define FC_INITPYDATA FC_FUNC(initpydata, INITPYDATA)
  void FC_INITPYDATA();
  
}
void call_pyinit(const char* frame, const char* beam, const char* target, double win); 
void call_pygive(const char* frame ); 

void call_ptime(const char * name, int j, int k);
void call_steer();
void call_casini();
void call_cascade();
void call_cascha();
void call_pytcha();
void call_aricha();
void call_arinit(const char * name);

// A pythia routine
void call_pyhepc(int mode);

void call_caend(int i);
void call_event();
void call_caupevnt();
// This is for setting the random seed
//void call_rm48in(int ISEED, int N1, int N2);
#endif
