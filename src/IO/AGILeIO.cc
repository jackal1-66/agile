// -*- C++ -*-

#include "AGILe/AGILe.hh"
#include "AGILe/GeneratorState.hh"

#include "TinyXML/tinyxml.h"

namespace AGILe{

  ostream &operator<<(ostream &os, const GeneratorState &state){

    TiXmlDocument doc;

    TiXmlElement hepml("hepml");

    doc.InsertEndChild(hepml);

    TiXmlElement* docRoot = doc.RootElement();

    TiXmlElement collision("collision");

    vector<TiXmlElement> pdfElements;
    
    vector<Beam> beams = state.getBeams();

    bool gotBeams = false;
    
    for(vector<Beam>::iterator beamIt = beams.begin();
        beamIt != beams.end(); ++beamIt){
      TiXmlElement beamElement("particle");
      beamElement.SetAttribute("name", beamIt->name);
      beamElement.SetAttribute("id", beamIt->position);

      TiXmlElement momentumElement("momentum");
      momentumElement.SetAttribute("unit", "GeV");

      stringstream s;
      s<<beamIt->energy;
      TiXmlText val(s.str());
      momentumElement.InsertEndChild(val);
      beamElement.InsertEndChild(momentumElement);
      collision.InsertEndChild(beamElement);
      gotBeams = true;
      
      TiXmlElement pdfEl("pdf");
      PDF pdf = state.getPDF(beamIt->name);
      pdfEl.SetAttribute("set", pdf.set);
      pdfEl.SetAttribute("member", pdf.member);
      pdfEl.SetAttribute("scheme", pdf.scheme);
      TiXmlElement pdfParticle("particle");
      pdfParticle.SetAttribute("name", pdf.particleId);
      pdfEl.InsertEndChild(pdfParticle);
      pdfElements.push_back(pdfEl);
    }

    TiXmlElement reaction("reaction");
    
    if(gotBeams) reaction.InsertEndChild(collision);

    docRoot->InsertEndChild(reaction);

    TiXmlElement runseries("runseries");

    TiXmlElement run("run");

    TiXmlElement seedElements("randomSeed");

    vector<int> seeds = state.getSeeds();
    
    int seedIndex = 1;
    
    bool gotSeeds = false;

    for(vector<int>::iterator seedIt = seeds.begin();
	seedIt!=seeds.end(); ++seedIt){
      TiXmlElement seed("seed");
      seed.SetAttribute("index", seedIndex);
      stringstream s;
      s<<*seedIt;
      TiXmlText val(s.str());
      seed.InsertEndChild(val);
      seedElements.InsertEndChild(seed);
      ++seedIndex;
      gotSeeds = true;
    }
    
    if(gotSeeds) run.InsertEndChild(seedElements);

    TiXmlElement normalisation("normalisation");
    TiXmlElement crossSection("crossSection");
    crossSection.SetAttribute("unit", "pb^-1");
    stringstream s;
    s<<state.getCrossSection();
    TiXmlText csText(s.str());
    crossSection.InsertEndChild(csText);
    normalisation.InsertEndChild(crossSection);
    s.str("");
    s<<state.getNEvents();
    TiXmlElement nEvents("numberOfEvents");    
    TiXmlText nText(s.str());
    nEvents.InsertEndChild(nText);
    normalisation.InsertEndChild(nEvents);
    TiXmlElement lumi("luminosity");
    run.InsertEndChild(normalisation);

    TiXmlElement genSettings("generatorSettings");
    
    TiXmlElement gen("generator");
    gen.SetAttribute("name",state.name());
    gen.SetAttribute("version", state.version());
    genSettings.InsertEndChild(gen);
    
    for(vector<TiXmlElement>::iterator pdfIt = pdfElements.begin();
        pdfIt!=pdfElements.end(); ++pdfIt){
      genSettings.InsertEndChild(*pdfIt);
    }
    
    run.InsertEndChild(genSettings);
    runseries.InsertEndChild(run);

    docRoot->InsertEndChild(runseries);

    os<<doc;
    os<<endl;

    return os;
  }

}
