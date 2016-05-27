// -*- C++ -*-
#ifndef AGILE_HEPMCTOOLS_HH
#define AGILE_HEPMCTOOLS_HH

#include "HepMC/GenEvent.h"

namespace AGILe {


  inline void fixHepMCUnitsFromGeVmm(HepMC::GenEvent& evt) {
    #ifdef HEPMC_HAS_UNITS
    if (evt.momentum_unit() == HepMC::Units::MEV) {
      for (HepMC::GenEvent::particle_iterator p = evt.particles_begin(); p != evt.particles_end(); ++p) {
        const HepMC::FourVector fv((*p)->momentum().px() * 1000,
                                   (*p)->momentum().py() * 1000,
                                   (*p)->momentum().pz() * 1000,
                                   (*p)->momentum().e()  * 1000);
        (*p)->set_momentum( fv);
      }
    }
    if (evt.length_unit() == HepMC::Units::CM) {
      for (HepMC::GenEvent::vertex_iterator vtx = evt.vertices_begin(); vtx != evt.vertices_end(); ++vtx) {
        const HepMC::FourVector fv((*vtx)->position().x() / 10.,
                                   (*vtx)->position().y() / 10.,
                                   (*vtx)->position().z() / 10.,
                                   (*vtx)->position().t() / 10.);
        (*vtx)->set_position(fv);
      }
    }
    #endif
  }


}

#endif
