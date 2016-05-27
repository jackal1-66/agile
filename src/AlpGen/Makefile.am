lib_LTLIBRARIES = libAGILeAlpGen.la libAGILeAlpGenFPythia.la libAGILeAlpGenFHerwig.la libAGILeAlpGenFHerwigJimmy.la

## AlpGen
libAGILeAlpGen_la_SOURCES = AlpGen.cc 
libAGILeAlpGen_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeAlpGen_la_LIBADD  = $(FORTRANLIBADD)

## AlpGenFHerwig
libAGILeAlpGenFHerwig_la_SOURCES = AlpGenFHerwig.cc 
libAGILeAlpGenFHerwig_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeAlpGenFHerwig_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FHerwig/libAGILeFHerwig.la

## AlpGenFHerwigJimmy
libAGILeAlpGenFHerwigJimmy_la_SOURCES = AlpGenFHerwigJimmy.cc 
libAGILeAlpGenFHerwigJimmy_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeAlpGenFHerwigJimmy_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FHerwig/libAGILeFHerwigJimmy.la

## AlpGenFPythia
libAGILeAlpGenFPythia_la_SOURCES = AlpGenFPythia.cc
libAGILeAlpGenFPythia_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeAlpGenFPythia_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FPythia/libAGILeFPythia.la 
