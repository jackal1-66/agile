EXTRA_DIST = __init__.py agilewrap.i

all-local: agilewrap_wrap.cc agilewrap.py
	@true

agilewrap_wrap.cc agilewrap.py: agilewrap.i
	$(SWIG) -c++ -python -I$(top_srcdir)/include -o agilewrap_wrap.cc $<

clean-local:
	@rm -f *.pyc
	@rm -f agilewrap.py
	@rm -f agilewrap_wrap.cc
