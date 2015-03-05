include $(top_srcdir)/Makefile.am.common
SUBDIRS = include src test external/gtest
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# pkg-config stuff, note that libdolly.pc is always required in order
# to get the correct library
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pkgconfig/libcinamo.pc
