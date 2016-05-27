#ifndef AGILE_FPHOJETWRAPPER62_HH
#define AGILE_FPHOJETWRAPPER62_HH

// Wrapper for FORTRAN version of Phojet 
//////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <cstring>
#include "AGILe/Phojet/PhojetWrapper.hh"


extern "C" {
  
  #define FC_PYJETS FC_FUNC(pyjets, PYJETS)
  const int pyjets_maxn = 4000;
  extern struct {
    int n, npad, k[5][pyjets_maxn];
    double p[5][pyjets_maxn], v[5][pyjets_maxn];
  } FC_PYJETS;


  #define FC_PYDAT1 FC_FUNC(pydat1, PYDAT1)
  extern struct {
    int mstu[200];
    double paru[200];
    int mstj[200];
    double parj[200];
  } FC_PYDAT1;


  #define FC_PYDAT2 FC_FUNC(pydat2, PYDAT2)
  extern struct {
    int kchg[4][500];
    double pmas[4][500], parf[2000], vckm[4][4];  
  } FC_PYDAT2;


  #define FC_PYDAT3 FC_FUNC(pydat3, PYDAT3)
  extern struct {
    int mdcy[3][500], mdme[2][8000];
    double brat[8000];
    int kfdp[5][8000];
  } FC_PYDAT3;


  #define FC_PYDATR FC_FUNC(pydatr, PYDATR)
  extern struct {
    int mrpy[6];
    double rrpy[100];
  } FC_PYDATR;


  #define FC_PYSUBS FC_FUNC(pysubs, PYSUBS)
  extern struct {
    int msel, mselpd, msub[500], kfin[81][2];
    double ckin[200];
  } FC_PYSUBS;


  #define FC_PYPARS FC_FUNC(pypars, PYPARS)
  extern struct {
    int mstp[200];
    double parp[200];
    int msti[200];
    double pari[200];
  } FC_PYPARS;


  #define FC_PYINT1 FC_FUNC(pyint1, PYINT1)
  extern struct {
    int mint[400];
    double vint[400];
  } FC_PYINT1;


  #define FC_PYINT2 FC_FUNC(pyint2, PYINT2)
  extern struct {
    int iset[500], kfpr[2][500];
    double coef[20][500];
    int icol[2][4][40]; // was [320] was [40][4][2]
  } FC_PYINT2;


  #define FC_PYINT5 FC_FUNC(pyint5, PYINT5)
  extern struct {
    int ngenpd, ngen[3][501];
    double xsec[3][501];
  } FC_PYINT5;

  #define FC_POMDLS FC_FUNC(pomdls, POMDLS)
  extern struct {
    const char* mdlna[50];
    int iswmdl[50];
    double parmdl[400];
    int ipamdl[400];
  } FC_POMDLS;

  #define FC_POPRCS FC_FUNC(poprcs, POPRCS)
  extern struct {
    int iproce;
    int idnodf;
    int idifr1;
    int idifr2;
    int iddpom;
    int ipron[15][4];
  } FC_POPRCS;

  #define FC_POGCMS FC_FUNC(pogcms, POGCMS)
  extern struct {
    double ecm;
    double pcm;
    double pmass[2];
    double pvirt[2];
    int ifpap[2];
    int ifpab[2];
  } FC_POGCMS;

  #define FC_POEVT2 FC_FUNC(poevt2, POEVT2)
  extern struct {
    int impart[10000];
    int iphist[2][10000];
    int icolor[2][10000];
  } FC_POEVT2;

}

#endif
