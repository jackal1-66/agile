EXTRA_DIST =

dist_pkgdata_DATA = \
  params/lep1.params \
  params/lhc900.params \
  params/lhc7000.params \
  params/lhc10000.params \
  params/lhc14000.params \
  params/tevatron630.params \
  params/tevatron1800.params \
  params/tevatron1960.params \
  params/rhic-pp200.params \
  params/hera296.params

dist_pkgdata_DATA += \
  params/fpythia-atlas-mc08.params \
  params/fpythia-atlas-mc09.params \
  params/fpythia-atlas-mc09c.params \
  params/fpythia-atlas-ambt1.params \
  params/fpythia-aleph.params \
  params/fpythia-cms-z1.params \
  params/fpythia-delphi.params \
  params/fpythia-atlaspdf.params \
  params/fpythia-Zee.params \
  params/fpythia-Zmumu.params \
  params/fpythia-Zeemumu.params \
  params/fpythia-Wenu.params \
  params/fpythia-Wmunu.params \
  params/fpythia-Wenumunu.params \
  params/fpythia-Zbb.params \
  params/fpythia-Zhadronic.params \
  params/fpythia-Zhadronic-delphi.params \
  params/fpythia-Zhadronic-aleph.params \
  params/fpythia-gammajet.params \
  params/fpythia-longlife-stable.params \
  params/fpythia-minbias.params \
  params/fpythia-zerobias.params \
  params/fpythia-dd.params \
  params/fpythia-nd.params \
  params/fpythia-sd.params \
  params/fpythia-nsd.params \
  params/fpythia-ttbar-semileptonic.params

dist_pkgdata_DATA += \
  params/fpythia-ALEPH_1996_S3196992.params \
  params/fpythia-CDF_2000_S4155203.params \
  params/fpythia-CDF_2001_S4751469.params \
  params/fpythia-CDF_2002_S4796047.params \
  params/fpythia-CDF_2004_S5839831.params \
  params/fpythia-CDF_2008_LEADINGJETS.params \
  params/fpythia-CDF_2008_NOTE_9351.params \
  params/fpythia-CDF_2009_S8233977.params \
  params/fpythia-D0_2001_S4674421.params \
  params/fpythia-D0_2004_S5992206.params \
  params/fpythia-D0_2006_S6438750.params \
  params/fpythia-D0_2007_S7075677.params \
  params/fpythia-D0_2008_S7719523.params \
  params/fpythia-D0_2008_S7837160.params \
  params/fpythia-D0_2008_S7554427.params \
  params/fpythia-D0_2008_S7863608.params

dist_pkgdata_DATA += \
  params/charybdisher-default.params \
  params/charybdispyt-default.params \
  params/falpher-default.params \
  params/falppyt-default.params

dist_pkgdata_DATA += \
  params/fherwig-atlas-mc08.params \
  params/fherwig-atlas-mc09-900.params \
  params/fherwig-atlas-mc09-7000.params \
  params/fherwig-atlas-mc09-10000.params \
  params/fherwig-atlas-mc09-14000.params \
  params/fherwig.qcd.params


## bash completion
if ENABLE_PYEXT

dist_pkgdata_DATA += agile-completion
bashcomp_dir = $(prefix)/etc/bash_completion.d
install-data-local:
	if [[ -d "$(bashcomp_dir)" && -w "$(bashcomp_dir)" ]]; then \
      install --mode 644 agile-completion $(bashcomp_dir)/; fi
uninstall-local:
	rm -f $(bashcomp_dir)/agile-completion

else

EXTRA_DIST += agile-completion

endif
