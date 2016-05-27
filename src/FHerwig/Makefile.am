lib_LTLIBRARIES = libAGILeFHerwig.la libAGILeFHerwigJimmy.la

## FHerwig
libAGILeFHerwig_la_SOURCES     = FHerwig.cc FHerwigDummyRoutines.f FHerwigWrapper.cc openlhef.f
libAGILeFHerwig_la_LDFLAGS     = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeFHerwig_la_LIBADD      = $(FORTRANLIBADD) 

## FHerwigJimmy
libAGILeFHerwigJimmy_la_SOURCES     = FHerwigJimmy.cc 
libAGILeFHerwigJimmy_la_LDFLAGS     = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeFHerwigJimmy_la_LIBADD      = $(FORTRANLIBADD)  libAGILeFHerwig.la
