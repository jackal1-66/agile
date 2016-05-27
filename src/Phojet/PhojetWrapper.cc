// -*- C++ -*-

#include "AGILe/Phojet/PhojetWrapper.hh"
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

void call_pho_setpar(int i,int id, int mode,double zero) {
  pho_setpar_(&i,&id, &mode, &zero);
}

void call_pho_init(int mode, int irej){
  pho_init_( &mode, &irej);
} 

void call_pho_event(int mode, double* _p1, double* _p2,
             double sigmax, int irej) {
  pho_event_(&mode, _p1, _p2, &sigmax,&irej);
}

void call_pho_hepevt() { 
  pho_hepevt_(); 
}

void call_pho_rndin(int rndm1, int rndm2, int rndm3, int rndm4) {
  pho_rndin_(&rndm1,&rndm2,&rndm3,&rndm4);
}
