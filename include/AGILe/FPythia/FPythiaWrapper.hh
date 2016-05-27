#ifndef AGILE_FPYTHIAWRAPPER_HH
#define AGILE_FPYTHIAWRAPPER_HH

#include <ctype.h>
#include "AGILe/FortranWrappers.hh"

extern "C" {
  #define FC_PYHEPC FC_FUNC(pyhepc, PYHEPC)
  void FC_PYHEPC(int*);
  #define FC_PYTUNE FC_FUNC(pytune, PYTUNE)
  void FC_PYTUNE(int*);
  #define FC_PYINIT FC_FUNC(pyinit, PYINIT)
  void FC_PYINIT(const char*, const char*, const char*, double*, int, int, int);
  #define FC_PYGIVE FC_FUNC(pygive, PYGIVE)
  void FC_PYGIVE(const char*, int);
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

  #define FC_LHEFOPEN FC_FUNC(openlhef, OPENLHEF)
  void FC_LHEFOPEN(const char*, int);
}

// Define methods to hide the subtle syntax necessary to call Fortran from C++
void call_pyhepc(int mode);
void call_pytune(int ntune);
void call_pyinit(const char* frame, const char* beam, const char* target, double win);
void call_pygive(const char* frame );
void call_pylist(int mode);
void call_pystat(int mode);
void call_pyevnt();
void call_lhefopen(const char* file);

#endif
