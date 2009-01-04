## Process this file with automake to produce Makefile.in

SUBDIRS = cgats numlib rspl
AM_CXXFLAGS = -Wall -O2 -DUNIX -I./numlib
AM_LDFLAGS = -Lrspl/ -lrspl -Lnumlib/ -largyllnum

check_PROGRAMS = rspltest

rspltest_SOURCES = rspltest.cpp

EXTRA_DIST = 
