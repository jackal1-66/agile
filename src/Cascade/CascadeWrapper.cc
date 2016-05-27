// -*- C++ -*-

#include "AGILe/Cascade/CascadeWrapper2.hh"
#include <cstring>

// Define methods to hide the subtle syntax necessary to call fortran from C++

void call_casini() { 
  casini_(); 
}

void call_ptime(const char *name, int j, int k) {
  ptime_(name, &j, &k);
}

void call_steer() {
  steer_();
}

void call_cascade() { 
  cascade_(); 
}

void call_cascha() { 
  cascha_(); 
}

void call_pytcha() { 
  pytcha_(); 
}

void call_pyinit( const char* frame, const char* beam, const char* target, double win ) { 
  pyinit_( frame, beam, target, &win, strlen(frame), strlen(beam), strlen(target) ); 
}

void call_pygive( const char* chin ) { 
  pygive_( chin, strlen(chin) ); 
}

void call_aricha() { 
  aricha_(); 
}

void call_arinit(const char *name) {
  arinit_(name);
}

void call_caend(int i) {
  caend_(&i);
}

void call_event() { 
  event_(); 
}

void call_caupevnt() { 
  caupevnt_(); 
}

// Pythia routines
void call_pyhepc( int mode ){ 
  pyhepc_( &mode ); 
}
//void call_rm48in(int ISEED, int N1, int N2) {
  //rm48in(&ISEED, &N1, &N2);
//}
