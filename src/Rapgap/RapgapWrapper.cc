// -*- C++ -*-

#include "AGILe/Rapgap/RapgapWrapper.hh"
#include <cstring>

// Define methods to hide the subtle syntax necessary to call fortran from C++

void call_graini() { 
  graini_(); 
}

void call_ptime(const char *name, int j, int k) {
  ptime_(name, &j, &k);
}

void call_steer() {
  steer_();
}

void call_rapgap() { 
  rapgap_(); 
}

void call_rapcha() { 
  rapcha_(); 
}

void call_hercha() { 
  hercha_(); 
}

void call_pytcha() { 
  pytcha_(); 
}

void call_aricha() { 
  aricha_(); 
}

void call_arinit(const char *name) {
  arinit_(name);
}

void call_raend(int i) {
  raend_(&i);
}

void call_event() { 
  event_(); 
}

// Pythia routines
void call_pyhepc( int mode ){ 
  pyhepc_( &mode ); 
}
//void call_rm48in(int ISEED, int N1, int N2) {
  //rm48in(&ISEED, &N1, &N2);
//}
