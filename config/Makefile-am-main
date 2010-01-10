### Makefile.am for the qhull package (main)
### Author: Rafael Laboissiere <rafael@debian.org>
### Created: Mon Dec  3 21:36:21 CET 2001

### Documentation files

# to:
docdir = $(prefix)/share/doc/$(PACKAGE)

# which:
doc_DATA =     \
  index.htm    \
  Announce.txt \
  COPYING.txt  \
  README.txt   \
  REGISTER.txt

### Extra files to be included in the tarball

EXTRA_DIST =   \
  $(doc_DATA)  \
  File_id.diz  \
  QHULL-GO.pif

### Subdirectories for Automaking

SUBDIRS = src html eg config
