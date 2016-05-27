#ifndef AGILE_PARTICLE_HH
#define AGILE_PARTICLE_HH

namespace AGILe {

  typedef int PdgCode;

  /// Enumeration of available beam particles (using PDG IDs where available)
  enum ParticleName { 
    ELECTRON = 11, 
    POSITRON = -11, 
    PROTON = 2212, 
    ANTIPROTON = -2212, 
    PHOTON = 22, 
    NEUTRON = 2112, 
    ANTINEUTRON = 2112, 
    MUON = 13, 
    ANTIMUON = -13,
    NU_E = 12, 
    NU_EBAR = -12,
    NU_MU = 14, 
    NU_MUBAR = -14,
    NU_TAU = 16, 
    NU_TAUBAR = -16, 
    PIPLUS = 211, 
    PIMINUS = -211,
    TAU = 15, 
    ANTITAU = -15,
    EMINUS = 11, 
    EPLUS = -11, 
    P = 2212, 
    PBAR = -2212,
    GAMMA = 22,
    ANY = 10000,
    PHOTOELECTRON,
    PHOTOPOSITRON,
    PHOTOMUON,     
    PHOTOANTIMUON,
    PHOTOTAU,      
    PHOTOANTITAU
  };


  //   /// Get the particle enum corresponding to the supplied string.
  //   inline const Particle strToBeam(const std::string& beamname) {
  //     if (beamname == "ELECTRON" || beamname == "E-") return ELECTRON;
  //     if (beamname == "POSITRON" || beamname == "E+") return POSITRON;
  //     if (beamname == "PROTON" || beamname == "P") return PROTON;
  //     if (beamname == "ANTIPROTON" || beamname == "PBAR") return ANTIPROTON;
  //     if (beamname == "PHOTON" || beamname == "GAMMA") return PHOTON;
  //     throw std::runtime_error("Couldn't parse beam string into a valid beam particle");
  //   }
  
}

#endif
