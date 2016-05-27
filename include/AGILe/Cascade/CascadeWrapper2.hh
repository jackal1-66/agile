#ifndef AGILE_CASCADE_WRAPPER2_HH
#define AGILE_CASCADE_WRAPPER2_HH

//////////////////////////////////////////////////////////////////////////
// Cascade common block declarations
// hschulz@physik.hu-berlin.de, February 2010
// Version 2.01 December 2007
// Wrapper for FORTRAN version of Cascade
//////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <cstring>
#include "AGILe/Cascade/CascadeWrapper.hh"


extern "C" {
  /// Cascade common block declarations.
  //Beams (to access info)
  #define FC_CABEAM FC_FUNC(cabeam, CABEAM)
  extern struct {
    double PBEAM[2];
    double KBEAM[2];
    double PBE1,PBE2;
  } FC_CABEAM;

  // Parameters for process steering 
  #define FC_CAINPU FC_FUNC(cainpu, CAINPU)
  extern struct {
    // int NFRAG,ILEPTO,IHF, ? 
    // not used: ISEMIH
    double PLEPIN,PPIN; //momenta of incoming lepton, proton
    //int LEPI,HADI; // PDGids of incoming particles
    int IFPS,INTER,ILHA; // parton shower, inclusion of priordial kt for diff processes, interaction type switch
  } FC_CAINPU;
 
  // ???
  #define FC_CAHERUP FC_FUNC(caherup, CAHERUP)
  extern struct {
    int Ilha; // Ilha sets treatment of remnants
  } FC_CAHERUP;


  // Parameters for nuber of generation tries... 
  #define FC_CAEFFIC FC_FUNC(caeffic, CAEFFIC)
  extern struct {
    double AVGI,SD;
    int NIN,NOUT;
  } FC_CAEFFIC;

  // Buchmueller ???
  #define FC_BUCHMUE FC_FUNC(buchmue, BUCHMUE)
  extern struct {
    double C1,Cg;
  } FC_BUCHMUE;

  // My first attempt, resolved photons, see manual section 4.7
  #define FC_COLCON FC_FUNC(colcon, COLCON)
  extern struct {
    int ICOLORA,IRESPRO,IRPA,IRPB,IRPC,IRPD,IRPE,IRPF,IRPG;
  } FC_COLCON;

  // Parameters for diffraction
  #define FC_DIFFR FC_FUNC(diffr, DIFFR)
  extern struct {
    double T2MAX,XF,ALPHP,RN2,EPSP,QMI,YMI,QMA,YMA;
    int NG,NPOM;
  } FC_DIFFR;

  // Parameters for hard subprocess selection (DIS)
  #define FC_DISDIF FC_FUNC(disdif, DISDIF)
  extern struct {
    int IDIR,IDISIDF;
  } FC_DISDIF;
  
  // Parameters for min/max electron scattering angle (degree)
  #define FC_ELECT FC_FUNC(elect, ELECT)
  extern struct {
    double THEMA,THEMI;
  } FC_ELECT;
  
  // Parameters for electroweak stuff: sin2thetaWeinberg, M_W^2
  #define FC_EWEAK FC_FUNC(eweak, EWEAK)
  extern struct {
    double SIN2W,MW2;
  } FC_EWEAK;
  
  // Parameters for structure function F2 ???
  #define FC_F2INT FC_FUNC(f2int, F2INT)
  extern struct {
    // double ? F2DIS,F2DIS,F2PI;
  } FC_F2INT;
  
  // Parameters for bookkeeping inside event record format???
  #define FC_HARD FC_FUNC(hard, HARD)
  extern struct {
    int NFT; // total number of final particles in 2to2 processes
    int NIA1,NIR1,NIA2,NIR2,NF1,NF2;
  } FC_HARD;
  
  
  // Parameters for exponential low Q2 suppression (possible tuning parameter)
  #define FC_LOWQ2 FC_FUNC(lowq2, LOWQ2)
  extern struct {
    double Q2SUPP;
  } FC_LOWQ2;

  // Parameters for accessing information of ???
  #define FC_MEINFO FC_FUNC(meinfo, MEINFO)
  extern struct {
    double ZQGKI,XPGKI,PHIGKI;
  } FC_MEINFO;
  
  // Parameters for 
  #define FC_OALPINI FC_FUNC(oalpini, OALPINI)
  extern struct {
    int IFULL,IQCDGRID; // Switches for lowest order or quark parton model process, O(a_S) generation on a grid
  } FC_OALPINI;
  
  // Parameters for 
  #define FC_PARAE FC_FUNC(parae, PARAE)
  extern struct {
    double Q2; // actual Q2 of gammas in lepto-production
    double Q2Q; // Scale mu^2 of hard scattering in a_S and structure functions
    // PCM???
  } FC_PARAE;
  
  // Parameters for 
  #define FC_PARAM FC_FUNC(param, PARAM)
  extern struct {
    double ALPHS,ALPH; // actual a_S, a_em
    double PI; // well ... pi!
    //double ? IWEI
  } FC_PARAM;
  
  // Parameters for 
  #define FC_PARAT FC_FUNC(parat, PARAT)
  extern struct {
    double AM[18]; // vector of final state particle masse
    double SHAT; // s^hat in hard sub processes
    double YMAX,YMIN; // upper and lower boundaries for y
    double QMAX,QMIN; // upper and lower boundaries for Q2 of photons
    double XMAX,XMIN; // upper and lower boundaries for x
  } FC_PARAT;
  
  // Parameters for random seed 
  #define FC_ISEED FC_FUNC(iseed, ISEED)
  extern struct {
    int ISEED;
  } FC_ISEED;
  
  // Parameters for PTCUT
  #define FC_PTCUT FC_FUNC(ptcut, PTCUT)
  extern struct {
    double PT2CUT[100];
  } FC_PTCUT;
  
  // Parameters for run setup
  #define FC_RAPA FC_FUNC(rapa, RAPA)
  extern struct {
    int IPRO;
  } FC_RAPA;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
  
  //// Parameters for 
  //#define FC_ FC_FUNC()
  //extern struct {
  //} FC_;
 

  
  
}

#endif
