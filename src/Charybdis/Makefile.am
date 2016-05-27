lib_LTLIBRARIES = \
	libAGILeCharybdis.la \
	libAGILeCharybdisFPythia.la \
	libAGILeCharybdisFHerwig.la \
	libAGILeCharybdisFHerwigJimmy.la

## General Charybdis support library
libAGILeCharybdis_la_SOURCES = Charybdis.cc

## CharybdisFHerwig
libAGILeCharybdisFHerwig_la_SOURCES = CharybdisFHerwig.cc
libAGILeCharybdisFHerwig_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeCharybdisFHerwig_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FHerwig/libAGILeFHerwig.la 

## CharybdisFHerwigJimmy
libAGILeCharybdisFHerwigJimmy_la_SOURCES = CharybdisFHerwigJimmy.cc
libAGILeCharybdisFHerwigJimmy_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeCharybdisFHerwigJimmy_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FHerwig/libAGILeFHerwigJimmy.la 

## CharybdisFPythia
libAGILeCharybdisFPythia_la_SOURCES = CharybdisFPythia.cc
libAGILeCharybdisFPythia_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeCharybdisFPythia_la_LIBADD  = $(FORTRANLIBADD) $(top_builddir)/src/FPythia/libAGILeFPythia.la
