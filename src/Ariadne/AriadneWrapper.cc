// -*- C++ -*-

#include "AGILe/Ariadne/AriadneWrapper.hh"
#include <cstring>

// Define methods to hide the subtle syntax necessary to call fortran from C++
void call_pyhepc( int mode ){ 

  pyhepc_( &mode ); 
}

void call_pyinit( const char* frame, const char* beam, const char* target, double win ) { 
  pyinit_( frame, beam, target, &win, strlen(frame), strlen(beam), strlen(target) ); 
}

void call_pygive( const char* chin ) { 
  pygive_( chin, strlen(chin) ); 
}

void call_pylist( int mode ) { 
  pylist_( &mode ); 
}

void call_pystat( int mode ) { 
  pystat_( &mode ); 
}

void call_pyevnt() { 
  pyevnt_(); 
}

void call_artune( const char* version ) {
  artune_( version, strlen(version) ); 
}

void call_arinit( const char* setup ) {
  arinit_( setup, strlen(setup) ); 
}

void call_arexec() { 
  arexec_(); 
}
void call_ariset( int in, float val) { 
  ariset_( &in, &val ); 
}
