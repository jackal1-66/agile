// -*- C++ -*-
#include "AGILe/Phojet/Phojet.hh"
#include "AGILe/Phojet/PhojetWrapper62.hh"
#include "AGILe/Utils.hh"
#include "AGILe/HepMCTools.hh"

#include "HepMC/HEPEVT_Wrapper.h"

namespace AGILe {

  // Author: S.Todorova


  /// Standard constructor
  Phojet::Phojet() {
    /// Pythia uses HEPEVT with 4000/10000 entries and 8-byte floats
    FC_PYJETS.n = 0; //< Ensure dummyness of the next call
    call_pyhepc(1);
    //HepMC::HEPEVT_Wrapper::set_max_number_entries(4000);
    //HepMC::HEPEVT_Wrapper::set_sizeof_real(8);
    HepMC::HEPEVT_Wrapper::set_max_number_entries(FC_PYDAT1.mstu[8-1]);
    //HepMC::HEPEVT_Wrapper::set_max_number_entries(10000);
    HepMC::HEPEVT_Wrapper::set_sizeof_real(8);

    // Start counting events at 1.
    _nevt = 1;

    // Initialize Phojet
    int irej=0;
    int mode = -1;
    FC_PHO_INIT(&mode,&irej);

    // Initialize Pythia PYDATA block data as external
    FC_INITPYDATA();

    // Write the full shower structure
    //setParam("MSTP(125)", 2);

    // Tell Pythia not to write multiple copies of particles in event record.
    //setParam("MSTP(128)", 2);

    // Set up particle names map
    /// @todo Also deal with gamma/e- etc. for resolved photoproduction...
    _particleNames[ELECTRON]    = "e-";
    _particleNames[POSITRON]    = "e+";
    _particleNames[PROTON]      = "p+";
    _particleNames[ANTIPROTON]  = "pbar-";
    _particleNames[NEUTRON]     = "n0";
    _particleNames[ANTINEUTRON] = "nbar0";
    _particleNames[PHOTON]      = "gamma";
    _particleNames[MUON]        = "mu-";
    _particleNames[ANTIMUON]    = "mu+";
    // TAU, ANTITAU
    _particleNames[NU_E]        = "nu_e";
    _particleNames[NU_EBAR]     = "nu_ebar";
    _particleNames[NU_MU]       = "nu_mu";
    _particleNames[NU_MUBAR]    = "nu_mubar";
    _particleNames[NU_TAU]      = "nu_tau";
    _particleNames[NU_TAUBAR]   = "nu_taubar";
    _particleNames[PIPLUS]      = "pi+";
    _particleNames[PIMINUS]     = "pi-";
    // PIZERO
    // PHOTOELECTRON, PHOTOPOSITRON,
    // PHOTOMUON,     PHOTOANTIMUON,
    // PHOTOTAU,      PHOTOANTITAU,
    /// For Pythia, other "normal" particles are:
    /// * gamma/e-, gamma/e+, gamma/mu-, gamma/mu+, gamma/tau-, gamma/tau+, pi0
    /// Also, with crappy PDF parameterisations and other defects:
    /// * K+, K-, KS0, KL0, Lambda0, Sigma-, Sigma0, Sigma+, Xi-, Xi0, Omega
    /// And, not useable at the moment:
    /// * pomeron, reggeon
  }


  void Phojet::setGenSpecificInitialState(PdgCode id1, double e1, PdgCode id2, double e2) {
    getLog() << Log::INFO << "Setting initial state..." << endl;
    // For Pythia, we have to hold on to this state until initialize() is called.
    _particleName1 = _particleNames[id1];
    _particleName2 = _particleNames[id2];

    _p1 = new double[4];
    _p2 = new double[4];

    (_p1)[0]=0.; (_p1)[1]=0.;
    (_p2)[0]=0.; (_p2)[1]=0.;
    (_p1)[3]=e1; (_p2)[3]=e2;

  }


  /// Set up default params etc.
  void Phojet::initialize() {
    Generator::initialize();

    double zero=0.;

    // hardcoded input !
    int i1=1;
    int i2=2;
    int id=2212;
    int mode = 0;
    FC_PHO_SETPAR(&i1,&id,&mode,&zero);
    FC_PHO_SETPAR(&i2,&id,&mode,&zero);

    double m = 0.93827;
    double m2 = m*m;
    double e = _p1[3];
    _pz = sqrt(e*e - m2);

    (_p1)[2]= _pz;
    (_p2)[2]=-_pz;

    double sigmax=0.;
    int irej=0;
    int mod0 = -1;

    FC_PHO_EVENT(&mod0,_p1,_p2, &sigmax, &irej);

    _initialized = true;

  }

  // Set a parameter with a string value
  bool Phojet::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);

    if (name.substr(0,5) == "IPRON" || name.substr(0,5) == "ipron") {
      size_t il = 0; size_t ir = 0; size_t ic = 0;
      while (il<name.size() && name.substr(il,1)!="(") il++;
      while (ic<name.size() && name.substr(ic,1)!=",") ic++;
      while (ir<name.size() && name.substr(ir,1)!=")") ir++;
      size_t ip1 = 0; size_t ip2 = 0;
      if (il > 3 && ic > il) {
        const string& num1 = name.substr(il+1,ic-il-1);
        ip1 = std::atoi(num1.c_str());
      }
      if (ic > 3 && ir > ic) {
        const string& num2 = name.substr(ic+1,ir-ic-1);
        ip2 = std::atoi(num2.c_str());
      }
      double val = std::atof(value.c_str());

      //std::cout <<"old value:"<<FC_POPRCS.ipron[ip1-1][ip2-1]<<std::endl;
      FC_POPRCS.ipron[ip1-1][ip2-1] = int(val);
      //std::cout <<"new value:"<<FC_POPRCS.ipron[ip1-1][ip2-1]<<std::endl;
    } else if (name.substr(0,6)=="ISWMDL" || name.substr(0,6)=="iswmdl" ) {
      size_t il = 0; size_t ir = 0;
      while (il<name.size() && name.substr(il,1)!="(") il++;
      while (ir<name.size() && name.substr(ir,1)!=")") ir++;
      size_t ip = 0;
      if (il>3 && ir>il ) {
        const string& num = name.substr(il+1,ir-il-1);
        ip = std::atoi(num.c_str());
      }
      double val = std::atof(value.c_str());

      //std::cout <<"old value:"<<FC_POMDLS.iswmdl[ip-1]<<std::endl;
      FC_POMDLS.iswmdl[ip-1] = int(val);
      //std::cout <<"new value:"<<FC_POMDLS.iswmdl[ip-1]<<std::endl;
    } else if (name.substr(0,6)=="IPAMDL" || name.substr(0,6)=="ipamdl" ) {
      size_t il =0; size_t ir = 0;
      while (il<name.size() && name.substr(il,1)!="(") il++;
      while (ir<name.size() && name.substr(ir,1)!=")") ir++;
      size_t ip=0;
      if (il>3 && ir>il ) {
        const string&  num= name.substr(il+1,ir-il-1);
        ip = std::atoi(num.c_str());
      }
      double val = std::atof(value.c_str());

      //std::cout <<"old value:"<<FC_POMDLS.ipamdl[ip-1]<<std::endl;
      FC_POMDLS.ipamdl[ip-1] = int(val);
      //std::cout <<"new value:"<<FC_POMDLS.ipamdl[ip-1]<<std::endl;
    } else if (name.substr(0,6)=="PARMDL" || name.substr(0,6)=="parmdl" ) {
      size_t il = 0; size_t ir = 0;
      while (il<name.size() && name.substr(il,1)!="(") il++;
      while (ir<name.size() && name.substr(ir,1)!=")") ir++;
      size_t ip = 0;
      if (il>3 && ir>il ) {
        const string&  num= name.substr(il+1,ir-il-1);
        ip = std::atoi(num.c_str());
      }
      double val = std::atof(value.c_str());

      //std::cout <<"old value:"<<FC_POMDLS.parmdl[ip-1]<<std::endl;
      FC_POMDLS.parmdl[ip-1] = val;
      //std::cout <<"new value:"<<FC_POMDLS.parmdl[ip-1]<<std::endl;
    } else if (name.substr(0,4)=="RNDM" || name.substr(0,4)=="rndm" ) {

      double val = std::atof(value.c_str());
      int ir1=int(val/100.);
      int rndm1=int(val-100*ir1);
      int ir2=int(ir1/100.);
      int rndm2=int(ir1-100*ir2);
      int ir3=int(ir2/100.);
      int rndm3=int(ir2-100*ir3);
      int rndm4=ir3;
      rndm1 = max(rndm1,1);
      rndm2 = max(rndm2,1);
      rndm3 = max(rndm3,1);
      rndm4 = max(rndm4,1);
      rndm4 = min(rndm4,178);
      //std::cout << " RNDM init with input:"<<rndm1<<":"<<rndm2<<":"<<rndm3<<":"<<rndm4 << std::endl;
      FC_PHO_RNDIN(&rndm1,&rndm2,&rndm3,&rndm4);

    } else {
      const string pygive_input(toUpper(name) + "=" + value);
      call_pygive(pygive_input.c_str());
    }
    return SUCCESS;
  }

  // Run the generator for one event
  void Phojet::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    /// @todo Allow control of choice of underlying event and shower evolutions via "meta-params".
    // Generate one event.
    // run Phojet
    double sigcur = 0.;
    int irej = 0;
    int mod = 1;

    FC_PHO_EVENT(&mod,_p1,_p2,&sigcur,&irej);

    //FC_PHO_HEPEVT();

    // Increment an event counter (Pythia does not count for itself).
    _nevt++;
    // fill the event using HepMC
    fillEvent(evt);
    evt.set_event_number(_nevt);
  }


  // Fill a HepMC event
  void Phojet::fillEvent(HepMC::GenEvent& evt) {

    // check event first
    // bool iok = HepMC::HEPEVT_Wrapper::check_hepevt_consistency();

    _hepevt.fill_next_event(&evt);
    fixHepMCUnitsFromGeVmm(evt);
    #ifdef HEPMC_HAS_CROSS_SECTION
    HepMC::GenCrossSection xsec;
    const double xsecval = getCrossSection();
    const double xsecerr = getCrossSection() / std::sqrt(FC_PYPARS.msti[4]);
    getLog() << Log::DEBUG << "Writing cross-section = " << xsecval << " +- " << xsecerr << endl;
    xsec.set_cross_section(xsecval, xsecerr);
    evt.set_cross_section(xsec);
    #endif
  }


  string Phojet::getPDFSet(PdgCode pid) {
    switch(pid) {
    case PROTON:
    case ANTIPROTON:
      if (FC_PYPARS.mstp[51] == 1) {
        return "PYINTERNAL";
      } else if(FC_PYPARS.mstp[51] == 2) {
        return "PYLHAPDF";
      }
      break;

    case ELECTRON:
    case POSITRON:
      if (FC_PYPARS.mstp[55] == 1) {
        return "PYINTERNAL";
      } else if(FC_PYPARS.mstp[55] == 2) {
        return "PYLHAPDF";
      }
      break;
    default:
      break;
    }
    throw runtime_error("Unknown particle for PDF Set");
  }


  int Phojet::getPDFMember(PdgCode pid) {
    switch(pid) {
    case PROTON:
    case ANTIPROTON:
      return FC_PYPARS.mstp[50];
      break;
    case ELECTRON:
    case POSITRON:
      return FC_PYPARS.mstp[54];
      break;
    default:
      break;
    }
    throw runtime_error("Unknown particle for PDF Set");
  }


  string Phojet::getPDFScheme(PdgCode pid) const {
    switch(pid){
    case PROTON:
    case ANTIPROTON:
      if (FC_PYPARS.mstp[51]==1) {
        return "PYINTERNAL";
      } else if(FC_PYPARS.mstp[51]==2) {
        return "LHAPDF";
      }
      break;
    case ELECTRON:
    case POSITRON:
      if (FC_PYPARS.mstp[55]==1) {
        return "PYINTERNAL";
      } else if(FC_PYPARS.mstp[55]==2) {
        return "LHAPDF";
      }
      break;
    default:
      break;
    }
    throw runtime_error("Unknown particle for PDF Set");
  }


  const double Phojet::getCrossSection(){
    // _crossSection = FC_PYINT5.xsec[2][0] * 1e09;
    _crossSection = FC_PYPARS.pari[0] * 1e09;
    return _crossSection;
  }

  const string Phojet::getVersion(){
    stringstream s;
    s << FC_PYPARS.mstp[180] << "." << FC_PYPARS.mstp[181];
    return s.str();
  }

  // Tidy up after ourselves
  void Phojet::finalize() {
    getLog() << Log::INFO << "Finalising..." << endl;
    // Print out stats from run
    double sig=0.;
    int irej=0;
    int mod = -2;
    FC_PHO_EVENT(&mod,_p1,_p2, &sig, &irej);
  }


}


extern "C" {
  AGILe::Generator* create() { return new AGILe::Phojet(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
