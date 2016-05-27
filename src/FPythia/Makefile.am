lib_LTLIBRARIES = libAGILeFPythia.la libAGILeFPythia_pyevwt.la

libAGILeFPythia_la_SOURCES = FPythia.cc FPythiaWrapper.cc initpydata.f openlhef.f
libAGILeFPythia_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeFPythia_la_LIBADD  = $(FORTRANLIBADD)

libAGILeFPythia_pyevwt_la_SOURCES = pyevwt.f
libAGILeFPythia_pyevwt_la_LDFLAGS = $(FORTRANLDFLAGS) $(DLOPENFLAGS) $(VERSIONFLAGS)
libAGILeFPythia_pyevwt_la_LIBADD  = $(FORTRANLIBADD)

