SUBDIRS = Core Tools IO
SUBDIRS += FPythia FHerwig AlpGen Charybdis Rapgap Cascade Phojet Ariadne
SUBDIRS += .

## Top-level AGILe library
lib_LTLIBRARIES = libAGILe.la
libAGILe_la_SOURCES  =
libAGILe_la_LIBADD   = \
  Core/libAGILeCore.la \
  Tools/libAGILeTools.la \
  IO/libAGILeIO.la \
  -L$(HEPMCLIBPATH) -l$(HEPMCLIBNAME)
