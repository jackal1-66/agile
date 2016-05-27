%module agilewrap

%{
  #define SWIG_FILE_WITH_INIT
  #include "AGILe/AGILe.hh"
  #include "AGILe/Loader.hh"
  #include "AGILe/Generator.hh"
  #include "AGILe/Run.hh"
  #include "AGILe/Tools/Logging.hh"
%}

// HepMC
//%include "hepmc.i"

// STL templates
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%template(StrList) std::vector<std::string>;
%template(LogLevelMap) std::map<std::string, int>;

// Version and path info
namespace AGILe {
  std::string version();
  std::string getLibPath();
  std::string getDataPath();
  std::string getAGILeDataPath();
  std::vector<std::string> getGenPaths();
  std::string getLCGPlatformTag();
}

// Logging interface
// Not mapping whole log interface, since we only want to be able to set log levels.
//%template(LogLevelMap) std::map<std::string, int>;
%ignore operator<<;
namespace AGILe {
  %rename(setLogLevel) Log::setLevel(const std::string&, int);
  class Log {
  public:
    enum Level {
      TRACE = 0, DEBUG = 10, INFO = 20, WARNING = 30, WARN = 30, ERROR = 40, CRITICAL = 50, ALWAYS = 50
    };
    static void setLevel(const std::string& name, int level);
  protected:
    Log(const std::string& name);
    Log(const std::string& name, int level);
  };
}
//%include "AGILe/Tools/Logging.hh"

%include "AGILe/Particle.hh"

namespace AGILe {
  %ignore Generator::getState;
  %ignore Generator::setState;
}
%include "AGILe/Generator.hh"

namespace AGILe {
  %ignore Run::Run(Generator&);
  %ignore Run::event;
}
%include "AGILe/Run.hh"

%include "AGILe/Loader.hh"
