#include "AGILe/Run.hh"

using namespace std;

namespace AGILe {


  Run::Run(Generator& gen)
    : _gen(&gen), _filter(Run::DOCFILT)//, _ostr(0), _io(0)
  {
    //
  }


  // Make a generator run with a particular gen and I/O target
  Run::Run(Generator& gen, const string& evtfile, int precision)
    : _gen(&gen), _filter(Run::DOCFILT)
  {
    if (evtfile.size() > 0) {
      if (evtfile == "-") {
        _io.reset(new HepMC::IO_GenEvent(std::cout));
      } else {
        // Ignore the HepMC::IO_GenEvent(filename, ios) constructor, since only available from HepMC >= 2.4
        _ostr.reset(new std::fstream(evtfile.c_str(), std::ios::out));
        _io.reset(new HepMC::IO_GenEvent(*_ostr));
      }
      // Use the cross-section #define as a proxy for precision() being available
      #ifdef HEPMC_HAS_CROSS_SECTION
      _io->precision(precision);
      #endif
    }
  }


  void filterEvent(HepMC::GenEvent* ge, Run::FilterLevel filterlevel) {
    // Escape fast if there's nothing to do
    if (filterlevel == Run::NOFILT) return;

    // We treat beam particles a bit specially
    const std::pair<HepMC::GenParticle*, HepMC::GenParticle*> beams = ge->beam_particles();

    // Make list of non-physical particle entries
    std::vector<HepMC::GenParticle*> unphys_particles;
    for (HepMC::GenEvent::particle_const_iterator pi = ge->particles_begin();
         pi != ge->particles_end(); ++pi) {
      // Beam particles might not have status = 4, but we want them anyway
      if (beams.first == *pi || beams.second == *pi) continue;
      // Filter by status
      const int status = (*pi)->status();
      const bool keep = (status == 1 || status == 4 || (filterlevel != Run::UNSTABLEFILT && status == 2));
      if (!keep) {
        unphys_particles.push_back(*pi);
      }
    }

    // Remove each unphysical particle from the list
    while (unphys_particles.size()) {
      HepMC::GenParticle* gp = unphys_particles.back();

      // Get start and end vertices
      HepMC::GenVertex* vstart = gp->production_vertex();
      HepMC::GenVertex* vend = gp->end_vertex();

      if (vend == vstart) {
        // Deal with loops
        vstart->remove_particle(gp);
      } else {

        // Connect decay particles from end vertex to start vertex
        /// @todo Have to build a list, since the GV::add_particle_out method modifies the end vertex!
        if (vend && vend->particles_out_size()) {
          std::vector<HepMC::GenParticle*> end_particles;
          for (HepMC::GenVertex::particles_out_const_iterator gpe = vend->particles_out_const_begin();
               gpe != vend->particles_out_const_end(); ++gpe) {
            end_particles.push_back(*gpe);
          }
          // Reset production vertices of child particles to bypass unphysical particle
          for (std::vector<HepMC::GenParticle*>::const_iterator gpe = end_particles.begin();
               gpe != end_particles.end(); ++gpe) {
            //std::cout << vstart << ", " << vend << std::endl;
            if (vstart) vstart->add_particle_out(*gpe);
          }
        } else {
          // If null end_vertex... stable unphysical particle?
        }

        // Delete unphysical particle and its orphaned end vertex
        delete vend;
        if (vstart) {
          delete vstart->remove_particle(gp);
        }
      }

      // Remove deleted particle from list
      unphys_particles.pop_back();
      //std::cout << unphys_particles.size() << std::endl;
    }

    // Delete any orphaned vertices
    std::vector<HepMC::GenVertex*> orphaned_vtxs;
    for (HepMC::GenEvent::vertex_const_iterator vi = ge->vertices_begin();
         vi != ge->vertices_end(); ++vi) {
      if ((*vi)->particles_in_size() == 0 && (*vi)->particles_out_size() == 0) {
        orphaned_vtxs.push_back(*vi);
      }
    }
    while (orphaned_vtxs.size()) {
      delete orphaned_vtxs.back();
      orphaned_vtxs.pop_back();
    }
  }



  // Generate an event and send it to the writer if it exists
  bool Run::makeEvent() {
    // Make and fill event
    _gen->makeEvent(_evt);

    // Filter unphysical bits of event (reduces storage/transport size, and ensures physicality)
    filterEvent(&_evt, _filter);

    // Do I/O streaming if required
    if (_io) {
      _io->write_event(&_evt);
      if (_io->rdstate() != 0) {
        return false;
      }
    }

    return true;
  }


  // Return an event summary string
  string Run::eventSummary() const {
    std::ostringstream ss;
    int Nfs = 0;
    for (HepMC::GenEvent::particle_const_iterator pi = _evt.particles_begin();
         pi != _evt.particles_end(); ++pi) {
      if ((*pi)->status() == 1) Nfs += 1;
    }
    ss << "HepMC::GenEvent { "
       << _evt.particles_size() << " particles "
       << "(" << Nfs << " in FS), "
       << _evt.vertices_size() << " vertices }";
    return ss.str();
  }


}
