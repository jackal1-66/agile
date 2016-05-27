noinst_LTLIBRARIES = libAGILeTools.la

dist_noinst_HEADERS = binreloc.h

libAGILeTools_la_SOURCES = Logging.cc binreloc.c AGILePaths.cc \
                           TinyXML/tinyxml.cpp TinyXML/tinyxmlerror.cpp TinyXML/tinyxmlparser.cpp

libAGILeTools_la_CPPFLAGS = $(AM_CPPFLAGS) \
  -I$(top_srcdir)/include/TinyXML \
  -DENABLE_BINRELOC \
  -DDEFAULTDATADIR=\"$(datadir)\" \
  -DDEFAULTLIBDIR=\"$(libdir)\" \
  -DLCGTAG=\""$(LCG_TAG)"\"
