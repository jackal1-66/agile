// -*- C++ -*-
#ifndef AGILE_GENERATOR_STATE_HH
#define AGILE_GENERATOR_STATE_HH

#include "AGILe/AGILe.hh"
#include "AGILe/Particle.hh"

namespace AGILe {

  struct Beam{
    PdgCode name;
    double energy;
    int position;
  };

  
  struct PDF{
    PdgCode particleId;
    string set;
    int member;
    string scheme;
  };

  
  class GeneratorState {
  public:

    GeneratorState() {
      _nEvents = 0;
      _crossSection = 0.0;
    }


    template <typename T>
    const GeneratorState& setParam(const string &name, const T &value) {
      stringstream s;
      s << value;
      return setParam(name, s.str());
    }


    const GeneratorState& setParam(const string & name, const string &value) {
      _stringParams[name] = value;
      return *this;
    }


    const GeneratorState& addSeed(const int &seed) {
      _seeds.push_back(seed);
      return *this;
    }


    const vector<int>& getSeeds() const {
      return _seeds;
    }

    
    /// @todo Why not return self?
    const bool setCrossSection(const double xs) {
      _crossSection = xs;
      return true;
    }

    
    const double getCrossSection() const {
      return _crossSection;
    }


    const int getNEvents()const {
      return _nEvents;
    }


    const GeneratorState& addEvent() {
      ++_nEvents;
      return *this;
    }


    const GeneratorState& setBeams(const Beam beam1,
                                   const Beam beam2) {
      _beams.clear();
      _beams.push_back(beam1);
      _beams.push_back(beam2);
      return *this;
    }


    const void addPDF(PDF pdf) {
      _pDFs[pdf.particleId] = pdf;
    }


    const GeneratorState& setName(const string& name) {
      _genName = name;
      return *this;
    }


    const void setVersion(const string& ver) {
      _genVersion = ver;
    }

    
    const string version() const {
      return _genVersion;
    }

    
    const string& name() const {
      return _genName;
    }

    
    const vector<Beam>& getBeams() const {
      return _beams;
    }


    const PDF& getPDF(PdgCode pid) const {
      map<PdgCode, PDF>::const_iterator pdfIt = _pDFs.find(pid);
      if (pdfIt!=_pDFs.end()) {
        return pdfIt->second;
      }
      throw runtime_error("PDF unknown for PDG code "+ pid);
    }
    

  private:

    vector<Beam> _beams;
    
    int _nEvents;
    double _luminosity;
    double _crossSection;

    string _genName;
    string _genVersion;
    
    map<PdgCode, PDF> _pDFs;
    
    vector<int> _seeds;
    map<string, string> _stringParams;
    
  };
  

  ostream &operator<<(ostream& os, const GeneratorState& state);

}
#endif
