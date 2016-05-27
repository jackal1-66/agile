ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src pyext include bin data test

#dist_pkgdata_DATA = agileenv.sh agileenv.csh

clean-local:
	@rm -rf a.out

pyclean:
	cd pyext && $(MAKE) clean

## Remove SVN dirs
dist-hook:
	@rm -rf `find $(distdir) -name ".svn"`

## Upload to HepForge
RSH=rsync
DEST=login.hepforge.org:agile/downloads/
upload: dist
	$(RSH) $(DIST_ARCHIVES) $(DEST)
