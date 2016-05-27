// -*- C++ -*-
#ifndef AGILE_RUN_HH
#define AGILE_RUN_HH

#include "AGILe/AGILe.hh"
#include "AGILe/Generator.hh"
#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"

namespace AGILe {


  /// @author Andy Buckley
  class Run {
  public:

    /// @brief Enum to specify the level of event format filtering to apply
    /// NOFILT = no filtering; DOCFILT = filter unphysical particles with status
    /// other than 1, 2, or 4; UNSTABLEFILT = filter as for DOCFILT, but also
    /// exclude any unstable particles with status = 2.
    enum FilterLevel { NOFILT=0, DOCFILT=1, UNSTABLEFILT=2 };

    /// Make a generator run with a particular gen
    Run(Generator& gen);

    /// Make a generator run with a particular gen and I/O target
    Run(Generator& gen, const std::string& evtfile="-", int precision=16);

    // /// Destructor
    // ~Run();

    /// Choose whether to filter out unphysical particles
    void setFilter(FilterLevel filt=DOCFILT) {
      _filter = filt;
    }

    /// Generate an event and send it to the writer if it exists
    bool makeEvent();

    /// Get the current generated event
    const HepMC::GenEvent& event() const {
      return _evt;
    }

    /// Return an event summary string
    std::string eventSummary() const;


  private:

    /// Generator used in this run
    Generator* _gen;

    /// Flag to decide whether or not to strip unphysical particles out of events
    FilterLevel _filter;

    /// Current HepMC event
    HepMC::GenEvent _evt;

    /// Output stream for HepMC writer
    shared_ptr<std::ostream> _ostr;

    /// HepMC I/O writer
    shared_ptr<HepMC::IO_GenEvent> _io;

  };


}

#endif
