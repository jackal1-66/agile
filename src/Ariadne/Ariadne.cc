// -*- C++ -*-
#include "AGILe/Ariadne/Ariadne.hh"
#include "AGILe/Ariadne/AriadneWrapper62.hh"
#include "AGILe/Utils.hh"
#include "AGILe/HepMCTools.hh"

#include "HepMC/HEPEVT_Wrapper.h"

namespace AGILe {

  // Author: Andy Buckley/ S.Todorova


  /// Standard constructor
  Ariadne::Ariadne() {
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

    // Initialize Pythia PYDATA block data as external
    FC_INITPYDATA();

    // Write the full shower structure
    setParam("MSTP(125)", 2);

    // Tell Pythia not to write multiple copies of particles in event record.
    setParam("MSTP(128)", 2);

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


  void Ariadne::setGenSpecificInitialState(PdgCode p1, double e1, PdgCode p2, double e2) {
    getLog() << Log::INFO << "Setting initial state..." << endl;
    // For Pythia, we have to hold on to this state until initialize() is called.
    _particleName1 = _particleNames[p1];
    _particleName2 = _particleNames[p2];
    /// @todo Get momenta and energies unconfused.
    _e1 = e1;
    _e2 = e2;
  }


  /// Set up default params etc.
  void Ariadne::initialize() {
    Generator::initialize();
    // call ariadne tune
    call_artune("4.12");
    //for (int i=20; i<25; i++) std::cout <<"para("<<i+1<<"):"<<FC_ARDAT1.para[i]<<std::endl;

    // Call pythia initialization with stored parameters as set by setGenSpecificInitialState()
    if (FC_PYPARS.mstp[142] != 1) {
      if (fuzzyEquals(_e1, _e2)) {
        call_pyinit("CMS", _particleName1.c_str(), _particleName2.c_str(), _e1+_e2);
      } else {
        stringstream p13cmd, p23cmd;
        p13cmd << "P(1,3) = " << _e1;
        p23cmd << "P(2,3) = " << -_e2;
        call_pygive("P(1,1) = 0.0");
        call_pygive("P(1,2) = 0.0");
        call_pygive(p13cmd.str().c_str());
        call_pygive("P(2,1) = 0.0");
        call_pygive("P(2,2) = 0.0");
        call_pygive(p23cmd.str().c_str());
        call_pyinit("3MOM", _particleName1.c_str(), _particleName2.c_str(), 0.0);
      }
    } else {
      // User process, parameters taken from LHAPDF initialisation file.
      call_pyinit("USER"," "," ", 0.0);
    }

    call_arinit("pythia");

    _initialized = true;

    // std::cout <<"check setup:"<<std::endl;
    // std::cout <<"PARA(1)  "<<FC_ARDAT1.para[0]<<std::endl;
    // std::cout <<"PARA(3)  "<<FC_ARDAT1.para[2]<<std::endl;
    // std::cout <<"PARJ(41)  "<<FC_PYDAT1.parj[40]<<std::endl;
    // std::cout <<"PARJ(42)  "<<FC_PYDAT1.parj[41]<<std::endl;

  }

  // Set a parameter with a string value
  bool Ariadne::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);
    if (name.substr(0,4)=="PARA" || name.substr(0,4)=="para" ) {
      size_t il = 0; size_t ir = 0;
      while (il<name.size() && name.substr(il,1)!="(") il++;
      while (ir<name.size() && name.substr(ir,1)!=")") ir++;
      if (il>3 && ir>il ) {
        const string&  num= name.substr(il+1,ir-il-1);
        int ip = std::atoi(num.c_str());
        float val = std::atof(value.c_str());
        //std::cout <<"old value:"<<FC_ARDAT1.para[ip-1]<<std::endl;
        FC_ARDAT1.para[ip-1] = val;
        //std::cout <<"new value:"<<FC_ARDAT1.para[ip-1]<<std::endl;
        call_ariset(ip,val);
        //std::cout <<"ARIADNE: PARA"<<"("<<ip<<") set to "<<value<<std::endl;
      }
    } else {
      const string pygive_input(toUpper(name) + "=" + value);
      call_pygive(pygive_input.c_str());
    }
    return SUCCESS;
  }

  // Run the generator for one event
  void Ariadne::makeEvent(HepMC::GenEvent& evt) {
    Generator::makeEvent(evt);
    /// @todo Allow control of choice of underlying event and shower evolutions via "meta-params".
    // Generate one event.
    call_pyevnt();
    // run Ariadne
    call_arexec();
    // Generate one event with new UE and shower.
    //call_pyevnw();
    // Convert common PYJETS into common HEPEVT.
    call_pyhepc(1);
    // Increment an event counter (Pythia does not count for itself).
    _nevt++;
    // fill the event using HepMC
    fillEvent(evt);
    evt.set_event_number(_nevt);
  }


  // Fill a HepMC event
  void Ariadne::fillEvent(HepMC::GenEvent& evt) {
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


  string Ariadne::getPDFSet(PdgCode pid) {
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


  int Ariadne::getPDFMember(PdgCode pid) {
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


  string Ariadne::getPDFScheme(PdgCode pid) const {
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


  const double Ariadne::getCrossSection(){
    // _crossSection = FC_PYINT5.xsec[2][0] * 1e09;
    _crossSection = FC_PYPARS.pari[0] * 1e09;
    return _crossSection;
  }

  const string Ariadne::getVersion(){
    stringstream s;
    s << FC_PYPARS.mstp[180] << "." << FC_PYPARS.mstp[181];
    return s.str();
  }

  // Tidy up after ourselves
  void Ariadne::finalize() {
    getLog() << Log::INFO << "Finalising..." << endl;
    // Print out stats from run
    call_pystat(1);
  }


}


extern "C" {
  AGILe::Generator* create() { return new AGILe::Ariadne(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
