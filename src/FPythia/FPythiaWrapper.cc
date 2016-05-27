// -*- C++ -*-

#include "AGILe/FPythia/FPythiaWrapper.hh"
#include <cstring>

void call_pyhepc(int mode) {
  FC_PYHEPC(&mode);
}

void call_pytune(int ntune) {
  FC_PYTUNE(&ntune);
}

void call_pyinit(const char* frame, const char* beam, const char* target, double win) {
  FC_PYINIT(frame, beam, target, &win, strlen(frame), strlen(beam), strlen(target) );
}

void call_pygive(const char* chin) {
  FC_PYGIVE(chin, strlen(chin));
}

void call_pylist(int mode) {
  FC_PYLIST(&mode);
}

void call_pystat(int mode) {
  FC_PYSTAT(&mode);
}

void call_pyevnt() {
  FC_PYEVNT();
}

void call_lhefopen(const char* chin) {
  FC_LHEFOPEN(chin, strlen(chin));
}
