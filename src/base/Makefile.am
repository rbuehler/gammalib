## Process this file with automake to produce Makefile.in

# Set include directories
INCLUDES = -I$(top_srcdir)/include \
           -I$(top_builddir)/src \
           -I$(top_srcdir)/src/support

# Define sources for this directory
sources = GBase.cpp \
          GRegistry.cpp

# Build libtool library
noinst_LTLIBRARIES = libbase.la
libbase_la_SOURCES = $(sources)
libbase_la_LDFLAGS = -version-info $(GAMMALIB_LT_VERSION)
