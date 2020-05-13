MAJOR_VERSION = 2

MINOR_VERSION = 13

BUILD_NUMBER = 11185

RELEASE = $(MAJOR_VERSION).$(MINOR_VERSION).$(BUILD_NUMBER)

SUB_RELEASE = $(MAJOR_VERSION).$(MINOR_VERSION)

MAIN_RELEASE = $(MAJOR_VERSION)

DEPDIR = debug

LT_OBJDIR = .libs

BIN=$(prefix)/bin/msobkow/$(MAJOR_VERSION).0.$(MINOR)_VERSION

bindir=$(prefix)/bin/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)

bin_PROGRAMS = testcflib

testcflib_CXXFLAGS = -I. -I$(prefix)/include/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION) -I$(prefix)/include/msobkow/$(MAJOR_VERSION).0.$(MINOR_VERSION)

testcflib_SOURCES = testcflib.cpp

testcflib_LDFLAGS= -lmpfr -lxerces-c -luuid -l:libcflib.so.$(MAJOR_VERSION).0.$(MINOR_VERSION) -lstdc++fs

ACLOCAL_AMFLAGS= -Im4
