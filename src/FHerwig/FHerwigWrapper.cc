// -*- C++ -*-

#include "AGILe/FHerwig/FHerwigWrapper.hh"
#include <cstring>

void call_lhefopen(const char* chin) {
  FC_LHEFOPEN(chin, strlen(chin));
}
