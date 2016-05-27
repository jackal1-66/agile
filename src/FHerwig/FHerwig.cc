// -*- C++ -*-
#include "AGILe/FHerwig/FHerwig.hh"
#include "AGILe/FHerwig/FHerwigWrapper65.hh"
#include "AGILe/Utils.hh"
#include "AGILe/HepMCTools.hh"


namespace AGILe {

  namespace {
    const size_t AUTPDF_LENGTH = 20;
    const int SEED_OFFSET = 1799;
  }


  // Standard constructor
  FHerwig::FHerwig()
    : _doHadronise(true), _unitWeight(true), _iprocset(false)
  {
    _myName = "Herwig";

    /// Herwig 6.5 uses HEPEVT with 4000/10000 entries and 8-byte floats
    HepMC::HEPEVT_Wrapper::set_max_number_entries(FC_HWGETHEPEVTSIZE());
    HepMC::HEPEVT_Wrapper::set_sizeof_real(8);

    // Set up particle names map: note that they must be 8 characters long
    _particleNames[ELECTRON]    = "E-      ";
    _particleNames[POSITRON]    = "E+      ";
    _particleNames[PROTON]      = "P       ";
    _particleNames[ANTIPROTON]  = "PBAR    ";
    _particleNames[NEUTRON]     = "N       ";
    _particleNames[ANTINEUTRON] = "NBAR    ";
    _particleNames[PHOTON]      = "GAMMA   ";
    _particleNames[MUON]        = "MU-     ";
    _particleNames[ANTIMUON]    = "MU+     ";
    // TAU, ANTITAU
    _particleNames[NU_E]        = "NU_E    ";
    _particleNames[NU_EBAR]     = "NU_EBAR ";
    _particleNames[NU_MU]       = "NU_MU   ";
    _particleNames[NU_MUBAR]    = "NU_MUBAR";
    _particleNames[NU_TAU]      = "NU_TAU  ";
    _particleNames[NU_TAUBAR]   = "NU_TAUBR";
    _particleNames[PIPLUS]      = "PI+     ";
    _particleNames[PIMINUS]     = "PI-     ";
    // PIZERO
    // PHOTOELECTRON, PHOTOPOSITRON,
    // PHOTOMUON,     PHOTOANTIMUON,
    // PHOTOTAU,      PHOTOANTITAU,

    // Start counting events at 1.
    _nevt = 1;
  }


  // Set up initial state from supplied params
  void FHerwig::setGenSpecificInitialState(int p1, double e1, int p2, double e2) {
    MSG_DEBUG("Setting initial state...");
    // Herwig's initial state particles specification must be 8 chars long
    for (size_t i = 0; i < 8; ++i) {
      FC_HWBMCH.PART1[i] = _particleNames[ParticleName(p1)].c_str()[i];
      FC_HWBMCH.PART2[i] = _particleNames[ParticleName(p2)].c_str()[i];
    }
    // Set momenta / energies
    // NB. Beam ordering is significant (segfault if "wrong") for HERA-like initial states
    // Subtraction of (very rough!) beam particle masses to get momenta rather than energies
    if (p1 == PROTON || p1 == ANTIPROTON || p1 == NEUTRON) e1 = sqrt(e1*e1 - 1.0);
    if (p2 == PROTON || p2 == ANTIPROTON || p2 == NEUTRON) e2 = sqrt(e2*e2 - 1.0);
    // And set the common block values
    FC_HWPROC.PBEAM1 = e1;
    FC_HWPROC.PBEAM2 = e2;
  }


  // Run generator initialization
  void FHerwig::initialize() {
    Generator::initialize();

    // Use QCD 2->2 as the default process
    if (!_iprocset) FC_HWPROC.IPROC = 1500;

    // Print banner and initialise common blocks (requires initial state and IPROC to have been set)
    FC_HWIGIN();

    // for (size_t idhw = 1; idhw <= 458; ++idhw) {
    //  std::cout << idhw << "  " << FC_HWPROP.IDPDG[idhw] << std::endl;
    // }

    // Set banner printout control params
    FC_HWPRAM.IPRINT = 1; // Type of info to print
    FC_HWPRAM.PRNDEF = 1; // Enable/disable ASCII output

    // Set some system params which HWIGIN has initialised to silly values
    FC_HWPROC.MAXEV = 10000000; // Maximum number of events (irrelevant!)
    FC_HWEVNT.MAXER = 10000000; // Maximum number of allowed errors
    FC_HWEVNT.MAXPR = 0; // Number of events to print

    // Apply stored parameters
    _processParams();

    // Compute parameter-dependent constants
    FC_HWUINC();

    // Initialise elementary process
    FC_HWEINI();

    _initialized = true;
  }


  // Set random number seed
  void FHerwig::setSeed(const int value) {
    Generator::setSeed(value);
    setParam("SEED", value);
  }


  // Gather user-provided parameters, applying only IPROC and the beam params
  bool FHerwig::setParam(const string& name, const string& value) {
    Generator::setParam(name, value);
    if (name == "IPROC") {
      // 1610 = gg -> H -> WW; 1706 = qq -> ttbar; 2510 = ttH -> ttWW, ...
      MSG_INFO("Setting process code (IPROC) = " << asInt(value));
      FC_HWPROC.IPROC = asInt(value);
      _iprocset = true;
    } else if (name == "PBEAM1") {
      MSG_INFO("Setting beam 1 momentum (PBEAM1) = " << asDouble(value));
      FC_HWPROC.PBEAM1 = asDouble(value);
    } else if (name == "PBEAM2") {
      MSG_INFO("Setting beam 2 momentum (PBEAM2) = " << asDouble(value));
      FC_HWPROC.PBEAM2 = asDouble(value);
    // } else if (name == "EBEAM1") {
    //   MSG_INFO("Setting beam 1 energy (EBEAM1) = " << asDouble(value));
    //   FC_HWPROC.EBEAM1 = asDouble(value);
    // } else if (name == "EBEAM2") {
    //   MSG_INFO("Setting beam 2 energy (EBEAM2) = " << asDouble(value));
    //   FC_HWPROC.EBEAM2 = asDouble(value);
    } else if (name == "LHEF") {
      if(FC_HWPROC.IPROC>0) {
	FC_HWPROC.IPROC = -FC_HWPROC.IPROC;
	_iprocset=true;
	MSG_INFO("LHEF meta-param has been set: turn IPROC negative = "<< FC_HWPROC.IPROC);
      } else if (!_iprocset) {
	FC_HWPROC.IPROC = -1;
	_iprocset=true;
	MSG_INFO("LHEF meta-param has been set: set IPROC = "<< FC_HWPROC.IPROC);
      }
      MSG_INFO("LHEF meta-param has been set: calling OPEN *now* for LHE file = " << value);
      call_lhefopen(value.c_str());
    } else {
      _storedParams[name] = value;
    }
    return SUCCESS;
  }


  // Set parameters.
  bool FHerwig::_processParams() {
    typedef pair<string,string> strpair;
    foreach (const strpair& kv, _storedParams) {
      const string& name = kv.first;
      const string& value = kv.second;

      // Strings
      if (name.find("AUTPDF") != string::npos) {
        if (name == "AUTPDF(1)" || name == "AUTPDF") {
          MSG_INFO("Setting AUTPDF(1) = " << value);
          const size_t nch = (value.size() < AUTPDF_LENGTH) ? value.size() : AUTPDF_LENGTH-1;
          for (size_t i = 0; i < AUTPDF_LENGTH; ++i) {
            if (i < nch) {
              FC_HWPRCH.AUTPDF[0][i] = value.data()[i];
            } else {
              FC_HWPRCH.AUTPDF[0][i] = ' ';
            }
          }
        }
        if (name == "AUTPDF(2)" || name == "AUTPDF") {
          MSG_INFO("Setting AUTPDF(2) = " << value);
          const size_t nch = (value.size() < AUTPDF_LENGTH) ? value.size() : AUTPDF_LENGTH-1;
          for (size_t i = 0; i < AUTPDF_LENGTH; ++i) {
            if (i < nch) {
              FC_HWPRCH.AUTPDF[1][i] = value.data()[i];
            } else {
              FC_HWPRCH.AUTPDF[1][i] = ' ';
            }
          }
        }
      }

      // Integers (other than IPROC)
      else if (name == "SEED") {
        const int baseseed = asInt(value);
        MSG_INFO("Setting random seeds based on this value (SEED) = " << baseseed);
        FC_HWEVNT.NRN[0] = baseseed;
        FC_HWEVNT.NRN[1] = baseseed + SEED_OFFSET;
        FC_HWHARD.IBRN[0] = baseseed + 2*SEED_OFFSET;
        FC_HWHARD.IBRN[1] = baseseed + 3*SEED_OFFSET;
      } else if (name == "MAXPR") {
        MSG_INFO("Setting max event printouts (MAXPR) = " << asInt(value));
        FC_HWEVNT.MAXPR = asInt(value);
      } else if (name == "IPRINT") {
        MSG_INFO("Setting printout info code (IPRINT) = " << asInt(value));
        FC_HWPRAM.IPRINT = asInt(value);
      } else if (name == "CLDIR1") {
        MSG_INFO("Setting smearing of perturbative quark pT in light cluster fission (CLDIR(1)) = " << asInt(value));
        FC_HWPRAM.CLDIR[0] = asInt(value);
      } else if (name == "CLDIR2") {
        MSG_INFO("Setting smearing of perturbative quark pT in b cluster fission (CLDIR(2)) = " << asInt(value));
        FC_HWPRAM.CLDIR[1] = asInt(value);
      } else if (name == "IOPREM") {
        MSG_INFO("Setting model for treatment of remnant clusters (IOPREM) = " << asInt(value));
        FC_HWPRAM.IOPREM = asInt(value);
      } else if (name == "ISPAC") {
        MSG_INFO("Setting ISR forced branching IR behaviour (ISPAC) = " << asInt(value));
        FC_HWPRAM.ISPAC = asInt(value);
      } else if (name == "NFLAV") {
        MSG_INFO("Setting number of flavours (NFLAV) = " << asInt(value));
        FC_HWPRAM.NFLAV = asInt(value);
      } else if (name == "NSTRU") {
        MSG_INFO("Setting internal PDF ID... are you sure? (NSTRU) = " << asInt(value));
        FC_HWPRAM.NSTRU = asInt(value);
      } else if (name == "MODPDF") {
        MSG_INFO("Setting PDFLIB IDs for both beams (MODPDF(1&2)) = " << asInt(value));
        FC_HWPRAM.MODPDF[0] = asInt(value);
        FC_HWPRAM.MODPDF[1] = asInt(value);
      } else if (name == "MODPDF(1)") {
        MSG_INFO("Setting PDFLIB ID for beam 1 (MODPDF(1)) = " << asInt(value));
        FC_HWPRAM.MODPDF[0] = asInt(value);
      } else if (name == "MODPDF(2)") {
        MSG_INFO("Setting PDFLIB ID for beam 2 (MODPDF(2)) = " << asInt(value));
        FC_HWPRAM.MODPDF[1] = asInt(value);
      } else if (name == "IFLMAX") {
        MSG_INFO("Setting max quark flavour in photoproduction (IFLMAX) = " << asInt(value));
        FC_HWHARD.IFLMAX = asInt(value);
      } else if (name == "LRSUD") {
        MSG_INFO("Setting unit for reading Sudakov table (LRSUD) = " << asInt(value));
        FC_HWPRAM.LRSUD = asInt(value);
      } else if (name == "LWSUD") {
        MSG_INFO("Setting unit for writing Sudakov table (LWSUD) = " << asInt(value));
        FC_HWPRAM.LWSUD = asInt(value);
      } else if (name == "IAPHIG") {
        MSG_INFO("Setting gg->H top loop param (IAPHIG) = " << asInt(value));
        FC_HWHARD.IAPHIG = asInt(value);
      // } else if (name == "MODBOS") {
      //   MSG_INFO("Setting MODBOS = " << asInt(value));
      //   FC_HWBOSC.MODBOS[0] = asInt(value);

      // Doubles
      } else if (name == "ALPHEM") {
        MSG_INFO("Setting alpha_EM (ALPHEM) = " << asDouble(value));
        FC_HWPRAM.ALPHEM = asDouble(value);
      } else if (name == "PTMIN") {
        MSG_INFO("Setting minimum hard pt (PTMIN) = " << asDouble(value));
        FC_HWHARD.PTMIN = asDouble(value);
      } else if (name == "PTMAX") {
        MSG_INFO("Setting maximum hard pt (PTMAX) = " << asDouble(value));
        FC_HWHARD.PTMAX = asDouble(value);
      } else if (name == "PTPOW") {
        MSG_INFO("Setting power for reweight (PTPOW) = " << asDouble(value));
        FC_HWHARD.PTPOW = asDouble(value);
      } else if (name == "Q2WWMN") {
        MSG_INFO("Setting minimum Q2 in equivalent photon approximation (Q2WWMN) = " << asDouble(value));
        FC_HWHARD.Q2WWMN = asDouble(value);
      } else if (name == "Q2WWMX") {
        MSG_INFO("Setting maximum Q2 in equivalent photon approximation (Q2WWMX) = " << asDouble(value));
        FC_HWHARD.Q2WWMX = asDouble(value);
      } else if (name == "YWWMIN") {
        MSG_INFO("Setting minimum photon light-cone fraction in equivalent photon approximation (YWWMIN) = " << asDouble(value));
        FC_HWHARD.YWWMIN = asDouble(value);
      } else if (name == "YWWMAX") {
        MSG_INFO("Setting maximum photon light-cone fraction in equivalent photon approximation (YWWMAX) = " << asDouble(value));
        FC_HWHARD.YWWMAX = asDouble(value);
      } else if ( name =="WHMIN") {
        MSG_INFO("Setting min hadronic mass in photon-induced (DIS) processes (WHMIN) = " << asDouble(value));
        FC_HWHARD.WHMIN = asDouble(value);
      } else if ( name =="EMMIN") {
        MSG_INFO("Setting minimum DY boson mass (EMMIN) = "<< asDouble(value));
        FC_HWHARD.EMMIN = asDouble(value);
      } else if ( name =="EMMAX") {
        MSG_INFO("Setting maximum DY boson mass (EMMIN) = "<< asDouble(value));
        FC_HWHARD.EMMAX = asDouble(value);
      } else if ( name =="EMPOW") {
        MSG_INFO("Setting power for EM reweighting (EMPOW) = "<< asDouble(value));
        FC_HWHARD.EMPOW = asDouble(value);
      } else if ( name =="EMSCA") {
        MSG_INFO("Setting ??? for EM (EMSCA) = "<< asDouble(value));
        FC_HWHARD.EMSCA = asDouble(value);
      } else if (name == "PRECO") {
        MSG_INFO("Setting probability of cluster colour reassignment (PRECO) = " << asDouble(value));
        FC_HWUCLU.PRECO = asDouble(value);
      } else if (name == "PDFX0") {
        MSG_INFO("Setting maximum x for saturation effects (PDFX0) = " << asDouble(value));
        FC_HW6506.PDFX0 = asDouble(value);
      } else if (name == "PDFPOW") {
        MSG_INFO("Setting suppression of PDFs below x0 (PDFPOW) = " << asDouble(value));
        FC_HW6506.PDFPOW = asDouble(value);
      } else if (name == "BTCLM") {
        MSG_INFO("Setting remnant cluster mass param adjustment (BTCLM) = " << asDouble(value));
        FC_HWPRAM.BTCLM = asDouble(value);
      } else if (name == "CLMAX") {
        MSG_INFO("Setting cluster mass offset (CLMAX) = " << asDouble(value));
        FC_HWPRAM.CLMAX = asDouble(value);
      } else if (name == "CLPOW") {
        MSG_INFO("Setting exponent of cluster fission (CLPOW) = " << asDouble(value));
        FC_HWPRAM.CLPOW = asDouble(value);
      } else if (name == "CLSMR1") {
        MSG_INFO("Setting Gaussian quark pT smearing width for light clusters (CLSMR(1)) = " << asDouble(value));
        FC_HWPRAM.CLSMR[0] = asDouble(value);
      } else if (name == "CLSMR2") {
        MSG_INFO("Setting Gaussian quark pT smearing width for b clusters (CLSMR(2)) = " << asDouble(value));
        FC_HWPRAM.CLSMR[1] = asDouble(value);
      } else if (name == "PRSOF") {
        MSG_INFO("Setting probablility of soft scatters (PRSOF) = " << asDouble(value));
        FC_HWPRAM.PRSOF = asDouble(value);
      } else if (name == "PSPLT1") {
        MSG_INFO("Setting cluster mass spectrum exponent for light clusters (PSPLT(1)) = " << asDouble(value));
        FC_HWPRAM.PSPLT[0] = asDouble(value);
      } else if (name == "PSPLT2") {
        MSG_INFO("Setting cluster mass spectrum exponent for b clusters (PSPLT(2)) = " << asDouble(value));
        FC_HWPRAM.PSPLT[1] = asDouble(value);
      }
      // Following params are useful for MPI/ISR tunes:
      else if (name == "PTRMS") {
        MSG_INFO("Setting intrinsic kT (PTRMS) = " << asDouble(value));
        FC_HWPRAM.PTRMS = asDouble(value);
      } else if (name == "QCDLAM") {
        MSG_INFO("Setting Lambda_QCD for alpha_s running (QCDLAM) = " << asDouble(value));
        FC_HWPRAM.QCDLAM = asDouble(value);
      } else if (name == "QSPAC") {
        MSG_INFO("Setting Q cutoff for spacelike (ISR) shower (QSPAC) = " << asDouble(value));
        FC_HWPRAM.QSPAC = asDouble(value);
      } else if (name == "VGCUT") {
        MSG_INFO("Setting gluon virtuality cutoff in parton showers (VGCUT) = " << asDouble(value));
        FC_HWPRAM.VGCUT = asDouble(value);
      } else if (name == "VQCUT") {
        MSG_INFO("Setting quark virtuality cutoff in parton showers (VQCUT) = " << asDouble(value));
        FC_HWPRAM.VQCUT = asDouble(value);
      } else if (name == "ZMXISR") {
        MSG_INFO("Setting max. momentum fraction for photon ISR (ZMXISR) = " << asDouble(value));
        FC_HWHARD.ZMXISR = asDouble(value);
      }
      // End MPI/ISR tune params
      else if (name == "VPCUT") {
        MSG_INFO("Setting photon virtuality cutoff (VPCUT) = " << asDouble(value));
        FC_HWPRAM.VPCUT = asDouble(value);
      } else if (name == "OMEGA0") {
        MSG_INFO("Setting omega_0 param in Mueller-Tang pomeron for IPROC=2400 (OMEGA0) = " << asDouble(value));
        FC_HWHARD.OMEGA0 = asDouble(value);
      } else if (name == "ASFIXD") {
        MSG_INFO("Setting a_s param in Mueller-Tang pomeron for IPROC=2400 (ASFIXD) = " << asDouble(value));
        FC_HWHARD.ASFIXD = asDouble(value);
      } else if (name == "Q2MIN") {
        MSG_INFO("Setting minimum DIS Q2 (Q2MIN) = " << asDouble(value));
        FC_HWHARD.Q2MIN = asDouble(value);
      } else if (name == "Q2MAX") {
        MSG_INFO("Setting maximum DIS Q2 (Q2MAX) = " << asDouble(value));
        FC_HWHARD.Q2MAX = asDouble(value);
      } else if (name == "Q2POW") {
        MSG_INFO("Setting reweighting power in DIS Q2 (Q2POW) = " << asDouble(value));
        FC_HWHARD.Q2POW = asDouble(value);
      } else if (name == "Q2WWMN") {
        MSG_INFO("Setting Q2WWMN (Q2WWMN) = " << asDouble(value));
        FC_HWHARD.Q2WWMN = asDouble(value);
      } else if (name == "Q2WWMX") {
        MSG_INFO("Setting Q2WWMX (Q2WWMX) = " << asDouble(value));
        FC_HWHARD.Q2WWMX = asDouble(value);
      } else if (name == "QLIM") {
        MSG_INFO("Setting QLIM (QLIM) = " << asDouble(value));
        FC_HWHARD.QLIM = asDouble(value);
      } else if (name == "YBMIN") {
        MSG_INFO("Setting minimum Bjorken y=Q2/xs (YBMIN) = " << asDouble(value));
        FC_HWHARD.YBMIN = asDouble(value);
      } else if (name == "YBMAX") {
        MSG_INFO("Setting maximum Bjorken y=Q2/xs (YBMAX) = " << asDouble(value));
        FC_HWHARD.YBMAX = asDouble(value);
      } else if (name == "YJMIN") {
        MSG_INFO("Setting minimum ??? (YJMIN) = " << asDouble(value));
        FC_HWHARD.YJMIN = asDouble(value);
      } else if (name == "YJMAX") {
        MSG_INFO("Setting maximum ??? (YJMAX) = " << asDouble(value));
        FC_HWHARD.YJMAX = asDouble(value);
      } else if (name == "YWWMIN") {
        MSG_INFO("Setting minimum ??? (YWWMIN) = " << asDouble(value));
        FC_HWHARD.YWWMIN = asDouble(value);
      } else if (name == "YWWMAX") {
        MSG_INFO("Setting maximum ??? (YWWMAX) = " << asDouble(value));
        FC_HWHARD.YWWMAX = asDouble(value);
      } else if (name == "XX1") {
        MSG_INFO("Setting ??? (XX(1)) = " << asDouble(value));
        FC_HWHARD.XX[0] = asDouble(value);
      } else if (name == "XX2") {
        MSG_INFO("Setting ??? (XX(2)) = " << asDouble(value));
        FC_HWHARD.XX[1] = asDouble(value);
      } else if (name == "XLMIN") {
        MSG_INFO("Setting minimum ??? (XLMIN) = " << asDouble(value));
        FC_HWHARD.XLMIN = asDouble(value);
      } else if (name == "XXMIN") {
        MSG_INFO("Setting minimum ??? (XXMIN) = " << asDouble(value));
        FC_HWHARD.XXMIN = asDouble(value);
      } else if (name == "WHMIN") {
        MSG_INFO("Setting minimum ??? (WHMIN) = " << asDouble(value));
        FC_HWHARD.WHMIN = asDouble(value);
      } else if (name == "ZJMAX") {
        MSG_INFO("Setting maximum ??? (ZJMAX) = " << asDouble(value));
        FC_HWHARD.ZJMAX = asDouble(value);
      } else if (name == "TMNISR") {
        MSG_INFO("Setting minimum ??? (TMNISR) = " << asDouble(value));
        FC_HWHARD.TMNISR = asDouble(value);
      } else if (name == "ZMXISR") {
        MSG_INFO("Setting maximum ??? in ISR (ZMXISR) = " << asDouble(value));
        FC_HWHARD.ZMXISR = asDouble(value);
      } else if (name == "THMAX") {
        MSG_INFO("Setting maximum ??? (THMAX) = " << asDouble(value));
        FC_HWHARD.THMAX = asDouble(value);
      } else if (name == "Y4JT") {
        MSG_INFO("Setting ??? (Y4JT) = " << asDouble(value));
        FC_HWHARD.Y4JT = asDouble(value);
      } else if (name == "SINS") {
        MSG_INFO("Setting ??? (SINS) = " << asDouble(value));
        FC_HWHARD.SINS = asDouble(value);
      } else if (name == "PLTCUT") {
        MSG_INFO("Setting lifetime cut (PLTCUT) = " << asDouble(value));
        FC_HWDIST.PLTCUT = asDouble(value);
      } else if (name == "GAMW") {
        MSG_INFO("Setting W width (GAMW) = " << asDouble(value));
        FC_HWPRAM.GAMW = asDouble(value);
      } else if (name == "GAMZ") {
        MSG_INFO("Setting Z0 width (GAMZ) = " << asDouble(value));
        FC_HWPRAM.GAMZ = asDouble(value);
      } else if (name == "GAMZP") {
        MSG_INFO("Setting Z0/gamma width (GAMZP) = " << asDouble(value));
        FC_HWPRAM.GAMZP = asDouble(value);
      } else if (name == "H1MIX") {
        /// @todo Add meaning of param (Higgs mixing angle?)
        MSG_INFO("Setting H1MIX (H1MIX) = " << asDouble(value));
        FC_HWPRAM.H1MIX = asDouble(value);
      } else if (name == "PHIMIX") {
        /// @todo Add meaning of param (??? mixing angle?)
        MSG_INFO("Setting PHIMIX (PHIMIX) = " << asDouble(value));
        FC_HWPRAM.PHIMIX = asDouble(value);
      }
      // NB. The -1 C-Fortran array offset does not apply for RMASS, which is declared as (0:NMXRES).
      else if (name == "RMASS(1)") {
        MSG_INFO("Setting down mass (RMASS(1)) = " << asDouble(value));
        FC_HWPROP.RMASS[1] = asDouble(value);
      } else if (name == "RMASS(2)") {
        MSG_INFO("Setting up mass (RMASS(2)) = " << asDouble(value));
        FC_HWPROP.RMASS[2] = asDouble(value);
      } else if (name == "RMASS(3)") {
        MSG_INFO("Setting strange mass (RMASS(3)) = " << asDouble(value));
        FC_HWPROP.RMASS[3] = asDouble(value);
      } else if (name == "RMASS(4)") {
        MSG_INFO("Setting charm mass (RMASS(4)) = " << asDouble(value));
        FC_HWPROP.RMASS[4] = asDouble(value);
      } else if (name == "RMASS(5)") {
        MSG_INFO("Setting bottom mass (RMASS(5)) = " << asDouble(value));
        FC_HWPROP.RMASS[5] = asDouble(value);
      } else if (name == "RMASS(6)") {
        MSG_INFO("Setting top mass (RMASS(6)) = " << asDouble(value));
        FC_HWPROP.RMASS[6] = asDouble(value);
      } else if (name == "RMASS(198)") {
        MSG_INFO("Setting W+ mass (RMASS(198)) = " << asDouble(value));
        FC_HWPROP.RMASS[198] = asDouble(value);
      } else if (name == "RMASS(199)") {
        MSG_INFO("Setting W- mass (RMASS(199)) = " << asDouble(value));
        FC_HWPROP.RMASS[199] = asDouble(value);
      } else if (name == "RMASS(200)") {
        MSG_INFO("Setting Z0 mass (RMASS(200)) = " << asDouble(value));
        FC_HWPROP.RMASS[200] = asDouble(value);
      } else if (name == "RMASS(201)") {
        MSG_INFO("Setting H mass (RMASS(201)) = " << asDouble(value));
        FC_HWPROP.RMASS[201] = asDouble(value);
      } //...

      // Booleans (done as ints in Fortran)
      else if (name == "GENSOF") {
        MSG_INFO("Setting ... (GENSOF) = " << asInt(value));
        FC_HWEVNT.GENSOF = asInt(value);
      } else if (name == "AZSOFT") {
        MSG_INFO("Setting use of soft gluon azimuthal corellations on/off (AZSOFT) = " << asInt(value));
        FC_HWPRAM.AZSOFT = asInt(value);
      } else if (name == "CLRECO") {
        MSG_INFO("Setting inclusion of colour rearrangement on/off (CLRECO) = " << asInt(value));
        FC_HWUCLU.CLRECO = asInt(value);
      } else if (name == "AZSPIN") {
        MSG_INFO("Setting use of gloun spin azimuthal correlations on/off (AZSPIN) = " << asInt(value));
        FC_HWPRAM.AZSPIN = asInt(value);
      } else if (name == "ZPRIME") {
        MSG_INFO("Setting Z' flag (ZPRIME) = " << asInt(value));
        FC_HWPRAM.ZPRIME = asInt(value);
      } else if (name == "HARDME") {
        MSG_INFO("Setting hard matrix element flag (HARDME) = " << asInt(value));
        FC_HWPRAM.HARDME = asInt(value);
      } else if (name == "SOFTME") {
        MSG_INFO("Setting soft matrix element flag (SOFTME) = " << asInt(value));
        FC_HWPRAM.SOFTME = asInt(value);
      } else if (name == "NOSPAC") {
        MSG_INFO("Setting spacelike showers on/off (NOSPAC) = " << asInt(value));
        FC_HWPRAM.NOSPAC = asInt(value);
      } else if (name == "PRVTX") {
        MSG_INFO("Setting inclusion of vertex info in event printout on/off (PRVTX) = " << asInt(value));
        FC_HWPRAM.PRVTX = asInt(value);
      } else if (name == "PRNDEC") {
        MSG_INFO("Setting use of decimal in event printout (PRNDEC) = " << asInt(value));
        FC_HWPRAM.PRNDEC = asInt(value);
      } else if (name == "PRNDEF") {
        MSG_INFO("Setting stdout printout on/off (PRNDEF) = " << asInt(value));
        FC_HWPRAM.PRNDEF = asInt(value);
      } else if (name == "PRNTEX") {
        MSG_INFO("Setting LaTeX output on/off (PRNTEX) = " << asInt(value));
        FC_HWPRAM.PRNTEX = asInt(value);
      } else if (name == "PRNWEB") {
        MSG_INFO("Setting HTML output on/off (PRNWEB) = " << asInt(value));
        FC_HWPRAM.PRNWEB = asInt(value);
      } else if (name == "MIXING") {
        MSG_INFO("Setting neutral B mixing on/off (MIXING) = " << asInt(value));
        FC_HWDIST.MIXING = asInt(value);
      } else if (name == "NOWGT") {
        MSG_INFO("Setting unweighted generation (NOWGT) = " << asInt(value));
        FC_HWEVNT.NOWGT = asInt(value);
      } else if (name == "DoHadronisation") {
        MSG_INFO("Do hadronisation = " << value);
        _doHadronise = asBool(value);//...
      } else if (name == "unitWeight") {
        MSG_INFO("Using a weight value of 1 in unweighted events = " << value);
        _unitWeight = asBool(value);
        // Error
      } else {
        MSG_ERROR("Herwig doesn't have a parameter called " << name);
        return FAILURE;
      }

    }
    return SUCCESS;
  }


  // Run the generator for one event
  void FHerwig::makeEvent(HepMC::GenEvent& evt) {
    // Loop until event works
    while (true) {
      Generator::makeEvent(evt);
      FC_HWUINE();  // Initialize event
      FC_HWEPRO();  // Generate hard subprocess
      FC_HWBGEN();  // Generate parton cascade
      FC_HWDHOB();  // Do heavy quark decays
      if(_doHadronise){
        FC_HWCFOR();  // Do cluster formation
        FC_HWCDEC();  // Do cluster decays
        FC_HWDHAD();  // Do unstable particle decays
        FC_HWDHVY();  // Do heavy flavor decays
        FC_HWMEVT();  // Add soft underlying event
      }
      FC_HWUFNE();  // Finish event
      if (FC_HWEVNT.IERROR == 0) break;
    }
    // Fill event from HEPEVT
    fillEvent(evt);
    // Increment an event counter (Herwig does not count for itself).
    _nevt++;
  }


  /// Fill a HepMC event
  void FHerwig::fillEvent(HepMC::GenEvent& evt) {
    HepMC::IO_HERWIG hepevt;
    hepevt.fill_next_event(&evt);
    fixHepMCUnitsFromGeVmm(evt);
    evt.set_event_number(_nevt);

    // Set beam particle status = 4
    if (evt.valid_beam_particles()) {
      evt.beam_particles().first->set_status(4);
      evt.beam_particles().second->set_status(4);
    }

    // Rewrite status codes to match HepMC standard (2 -> 3, 195-199 -> 2)
    for (HepMC::GenEvent::particle_const_iterator p = evt.particles_begin(); p != evt.particles_end(); ++p) {
      if ((*p)->status() == 2) (*p)->set_status(3);
      if ((*p)->status() >= 195 && (*p)->status() <= 199) (*p)->set_status(2);
    }

    //IO_HERWIG::fillEvent does not fill the weight
    evt.weights().clear();
    if(FC_HWEVNT.NOWGT == 0 || !_unitWeight){
      evt.weights().push_back(FC_HWEVNT.EVWGT);
    }else{
      evt.weights().push_back(1.0);
    }

    // Cross-section
    #ifdef HEPMC_HAS_CROSS_SECTION
    HepMC::GenCrossSection xsec;
    const double xsecval = getCrossSection();
    const double xsecerr = getCrossSection() / std::sqrt(_nevt);
    MSG_DEBUG("Writing cross-section = " << xsecval << " +- " << xsecerr);
    xsec.set_cross_section(xsecval, xsecerr);
    evt.set_cross_section(xsec);
    #endif
  }


  // Return the beam number (0 or 1) of a particle.
  // Return -1 if not a beam particle
  int FHerwig::_beamNumber(PdgCode pid) {
    string pName = _particleNames[pid];
    string beamName = "";
    for (int i = 0; i < 8; ++i) {
      beamName += FC_HWBMCH.PART1[i];
    }
    if (beamName.compare(pName) == 0) return 0;

    for (int i = 0; i < 8; ++i) {
      beamName += FC_HWBMCH.PART2[i];
    }
    if (beamName.compare(pName) == 0) return 1;
    return -1;
  }


  string FHerwig::getPDFSet(PdgCode pid){
    const int beamNum = _beamNumber(pid);
    if (beamNum < 0) {
      throw runtime_error("PDFSet unknown for PDG code " + pid);
    }
    string autString = "";
    for (size_t ii = 0; ii != AUTPDF_LENGTH; ++ii) {
      autString += FC_HWPRCH.AUTPDF[beamNum][ii];
    }
    return autString;
  }


  int FHerwig::getPDFMember(PdgCode pid){
    const int beamNum = _beamNumber(pid);
    if (beamNum < 0) {
      throw runtime_error("PDFMember unknown for PDG code "+ pid);
    }
    const int member = FC_HWPRAM.MODPDF[beamNum];
    return member;
  }


  string FHerwig::getPDFScheme(PdgCode pid) const {
    return "LHAPDF";
  }


  const double FHerwig::getCrossSection(){
    _crossSection = 1000.0 * FC_HWEVNT.WGTSUM / ((float)FC_HWEVNT.NWGTS);
    return _crossSection;
  }


  /// Tidy up, print out run stats, etc.
  void FHerwig::finalize() {
    MSG_DEBUG("Finalising...");
    FC_HWEFIN();
  }


}


// Class factory
extern "C" {
  AGILe::Generator* create() { return new AGILe::FHerwig(); }
  void destroy(AGILe::Generator* gen) { delete gen; }
}
