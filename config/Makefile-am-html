### Makefile.am for the qhull package (html)
### Author: Rafael Laboissiere <rafael@debian.org>
### Created: Mon Dec  3 21:36:21 CET 2001

### Man pages (trick to get around .man extension)

%.1: %.man
	cp $< $@
CLEANFILES = *.1
man_MANS = rbox.1 qhull.1

### Documentation files

# to:
docdir = $(prefix)/share/doc/$(PACKAGE)
htmldir = $(docdir)/html

# which:
html_DATA =    \
  index.htm    \
  qconvex.htm  \
  qdelau_f.htm \
  qdelaun.htm  \
  qh--4d.gif   \
  qh--cone.gif \
  qh--dt.gif   \
  qh--geom.gif \
  qh--half.gif \
  qh--rand.gif \
  qh-eg.htm    \
  qh-faq.htm   \
  qh-get.htm   \
  qh-impre.htm \
  qh-in.htm    \
  qh-optc.htm  \
  qh-optf.htm  \
  qh-optg.htm  \
  qh-opto.htm  \
  qh-optp.htm  \
  qh-optq.htm  \
  qh-optt.htm  \
  qh-quick.htm \
  qhalf.htm    \
  qhull.htm    \
  qvoron_f.htm \
  qvoronoi.htm \
  rbox.htm

### Extra files to be included in the tarball

EXTRA_DIST =   \
  $(html_DATA) \
  qhull.man    \
  qhull.txt    \
  rbox.man     \
  rbox.txt
