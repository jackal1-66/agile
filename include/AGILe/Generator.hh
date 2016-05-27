// -*- C++ -*-
#ifndef AGILE_GENERATOR_HH
#define AGILE_GENERATOR_HH

#include "AGILe/AGILe.hh"
#include "AGILe/Utils.hh"
#include "AGILe/Particle.hh"
#include "AGILe/GeneratorState.hh"
#include "HepMC/GenEvent.h"


// Nice logging macros
#ifndef MSG_LVL
#define MSG_LVL(lvl, x) \
  do { \
    if (this->getLog().isActive(lvl)) { \
      this->getLog() << lvl << x << endl;   \
    } \
  } while (0)

#define MSG_TRACE(x)   MSG_LVL(Log::TRACE, x)
#define MSG_DEBUG(x)   MSG_LVL(Log::DEBUG, x)
#define MSG_INFO(x)    MSG_LVL(Log::INFO, x)
#define MSG_WARNING(x) MSG_LVL(Log::WARNING, x)
#define MSG_ERROR(x)   MSG_LVL(Log::ERROR, x)
#endif


namespace AGILe {


  /// @author Andy Buckley
  class Generator {
  public:

    /// Really just syntactic sugar for bool returns from setParam
    enum Result { SUCCESS=1, FAILURE=0 };


    /// Standard constructor.
    Generator() :
      _initialstateset(false),
      _initialized(false),
      _myName("GENERATOR"),
      _versionSet(false)
    { }


    /// Destructor.
    virtual ~Generator() { }


    /// Define initial state.
    void setInitialState(int p1 = PROTON, double e1 = 7000.0,
                         int p2 = PROTON, double e2 = 7000.0)
    {
      setGenSpecificInitialState(p1, e1, p2, e2);
      /// @todo Make sure it was successful - exception handling
      _initialstateset = true;
      Beam beam1, beam2;
      beam1.name = p1;
      beam2.name = p2;
      beam1.energy = e1;
      beam2.energy = e2;
      beam1.position = 1;
      beam2.position = 2;
      _myState.setBeams(beam1, beam2);
    }


    /// Get a generator state object.
    virtual const GeneratorState& getState() {
      string myName = getName();
      _myState.setName(myName);
      _myState.setVersion(getVersion());
      _myState.setCrossSection(getCrossSection());
      PDF pdf;
      foreach (Beam b, _myState.getBeams()) {
        pdf.particleId = b.name;
        pdf.set = getPDFSet(b.name);
        pdf.member = getPDFMember(b.name);
        pdf.scheme = getPDFScheme(b.name);
        _myState.addPDF(pdf);
      }
      return _myState;
    }


    /// Setup the generator from a generator state object.
    virtual void setState(const GeneratorState& state) {
      throw runtime_error("This ain't ready yet, it's just here as an interface placeholder. Sorry.");
    }


    /// Get the generator name.
    virtual const std::string getName() const {
      return _myName;
    }


    /// Set the generator version.
    virtual void setVersion(const std::string& version) {
      _myVersion = version;
      _versionSet = true;
    }


    /// @brief Get the generator version.
    /// This implementation is used as a last resort to determine the generator version.
    /// Ideally a specific generator will know its own version and overwrite
    /// this.  Some generators (e.g. FHerwig) don't know this.
    virtual const std::string getVersion() {
      if (!_versionSet) {
        /// @todo This getName() doesn't get used polymophically: fix it!
        MSG_ERROR("You asked the generator " //<< getName()
                  << " what version it is, but it doesn't know!\n"
                  << "You should set the version with a call to setVersion(string)");
        throw runtime_error("Version unknown for generator");
      }
      return _myVersion;
    }


    /// Get the PDF set used by the generator, e.g. HWLHAPDF (for herwig)
    /// or one of the default sets.
    virtual std::string getPDFSet(PdgCode pid) {
      throw runtime_error("Have not implemented getPDFSet in " + getName());
    }


    /// Get the PDF id number for a given particle
    virtual int getPDFMember(PdgCode pid) {
      throw runtime_error("Have not implemented getPDFMember in " + getName());
    }


    /// Get the PDF scheme used by the generator (LHAPDF or other)
    virtual std::string getPDFScheme(PdgCode pid) const {
      throw runtime_error("Have not implemented getPDFScheme in " + getName());
    }


    /// Set the random number generator seed.
    virtual void setSeed(const int value) {
      if (_initialized) {
        MSG_ERROR("Can't set seed: generator has already been initialized");
        throw (runtime_error("Tried to set RNG seed after generator initialization"));
      }
      _myState.addSeed(value);
    }


    /// Pass an int-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const int& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass an int-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const unsigned int& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass an int-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const long& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass an int-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const unsigned long& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
      throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass a double/float-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const double& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization.");
      }
      return setParam(name, toString(value));
    }


    /// Pass a double/float-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const float& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass a bool-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const bool& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      return setParam(name, toString(value));
    }


    /// Pass a string-valued parameter to the generator.
    virtual bool setParam(const std::string& name, const std::string& value) {
      if (_initialized) {
        MSG_ERROR("Can't set parameter " << name << ": generator has already been initialized");
        throw runtime_error("Tried to set param after generator initialization");
      }
      _myState.setParam(name, value);
      return true;
    }


    /// Run one event.
    virtual void makeEvent(HepMC::GenEvent& evt) {
      if (!_initialized) initialize();
      clearEvent(evt);
      _myState.addEvent();
    }


    /// Return the generated cross section in pb.
    virtual const double getCrossSection() {
      MSG_ERROR("getCrossSection not implemented in generator " << getName());
      throw runtime_error("Tried to access cross-section in Generator base class");
      return _crossSection;
    }


    /// Finalise.
    virtual void finalize() = 0;


  protected:

    /// Get named logger
    Log& getLog() const {
      return Log::getLog("AGILe." + getName());
    }


    /// Set initial state implementation details
    virtual void
    setGenSpecificInitialState(int p1 = PROTON, double e1 = 7000.0,
                               int p2 = PROTON, double e2 = 7000.0) = 0;


    /// Initialise.
    virtual void initialize() {
      if (!_initialstateset) setInitialState();
    }


    /// Clear the supplied event.
    virtual void clearEvent(HepMC::GenEvent& evt) {
      evt.clear();
    }


  protected:

    double _crossSection;

    /// Flag for detecting whether the setInitialState method has run.
    bool _initialstateset;

    /// Flag for detecting whether the initialization method has run.
    bool _initialized;

    /// Collection of translated names for particles
    map<PdgCode, std::string> _particleNames;

    /// Generator name
    string _myName;


  private:

    GeneratorState _myState;

    string _myVersion;

    bool _versionSet;
  };


  ////////////////////////////////////////////////


  /// Class factory for dynamic generator loading.
  typedef Generator* (*Creator)();


  /// Class destroyer for dynamic generator loading.
  typedef void Destroyer(Generator*);

}

#endif
