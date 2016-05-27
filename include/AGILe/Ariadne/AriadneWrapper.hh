#ifndef AGILE_FARIADNEWRAPPER_HH
#define AGILE_FARIADNEWRAPPER_HH

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
  #define FC_ARTUNE FC_FUNC(artune, ARTUNE)
  void FC_ARTUNE(const char*,int);
  #define FC_ARINIT FC_FUNC(arinit, ARINIT)
  void FC_ARINIT(const char*,int);
  #define FC_AREXEC FC_FUNC(arexec, AREXEC)
  void FC_AREXEC();
  #define FC_ARISET FC_FUNC(ariset, ARISET)
  void FC_ARISET(int*, float*);
}

// Define methods to hide the subtle syntax necessary to call Fortran from C++
void call_pyhepc(int mode);
void call_pyinit(const char* frame, const char* beam, const char* target, double win); 
void call_pygive(const char* frame ); 
void call_pylist(int mode);
void call_pystat(int mode);
void call_pyevnt();
void call_artune(const char* version);
void call_arinit(const char* setup);
void call_arexec();
void call_ariset(int in, float val);

#endif
